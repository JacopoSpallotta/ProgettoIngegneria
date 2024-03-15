#include <gtkmm.h>
#include <iostream>
#include <random>
#include <unistd.h>
#include <thread>
#include <chrono>
#include "con2redis.h"

double getRandomNumber(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

void redisUpdate(std::mutex* redisMutex, redisContext *c2r, redisReply *reply, char *gluc, char *comp_dose, char *time_str, char *delta_str){
    while (true){
        (*redisMutex).lock();

        reply = RedisCommand(c2r, "XREADGROUP GROUP diameter screen COUNT 1 BLOCK 10000000000 NOACK STREAMS %s >", "gluc_displ");
        ReadStreamMsgVal(reply,0,0,1,gluc);

        reply = RedisCommand(c2r, "XREADGROUP GROUP diameter screen COUNT 1 BLOCK 10000000000 NOACK STREAMS %s >", "ins_displ");
        ReadStreamMsgVal(reply,0,0,1, comp_dose);        

        char delta_int[10];
        reply = RedisCommand(c2r, "XREADGROUP GROUP diameter screen COUNT 1 BLOCK 10000000000 NOACK STREAMS %s >", "delta_displ");
        ReadStreamMsgVal(reply,0,0,1, delta_int);
        if(strcmp(delta_int, "0") == 0){
            sprintf(delta_str, "Not eating");
        }else{
            sprintf(delta_str, "Eating");
        }

        reply = RedisCommand(c2r, "XREADGROUP GROUP diameter screen COUNT 1 BLOCK 10000000000 NOACK STREAMS %s >", "time_displ");
        ReadStreamMsgVal(reply,0,0,1, time_str);

        (*redisMutex).unlock();
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
    }
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    redisContext *c2r;
    redisReply *reply;
    int pid = getpid();
    char gluc[10];
    char comp_dose[10];
    char time_str[10];
    char delta_str[20];

    std::mutex redisMutex;

    printf("main(): pid %d: user screen: connecting to redis ...\n", pid);
    c2r = redisConnect("localhost", 6379);
    printf("main(): pid %d: user screen: connected to redis\n", pid);

    reply = RedisCommand(c2r, "DEL %s", "gluc_displ");
    reply = RedisCommand(c2r, "DEL %s", "ins_displ");
    reply = RedisCommand(c2r, "DEL %s", "delta_displ");
    reply = RedisCommand(c2r, "DEL %s", "time_displ");

    initStreams(c2r, "gluc_displ");
    initStreams(c2r, "ins_displ");
    initStreams(c2r, "delta_displ");
    initStreams(c2r, "time_displ");

    Gtk::Window window;
    window.set_default_size(900, 450);
    window.override_background_color(Gdk::RGBA("#2e3436"), Gtk::STATE_FLAG_NORMAL);
    window.set_border_width(10);

    Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();
    cssProvider->load_from_data(".my-box { background-color: #a8af7b; }");

    window.get_style_context()->add_provider(cssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    Gtk::Box vbox(Gtk::ORIENTATION_VERTICAL, 0);  
    vbox.get_style_context()->add_class("my-box");

    Gtk::Grid grid;
    grid.set_column_spacing(30);
    grid.set_row_spacing(20);

    Pango::FontDescription fontDescription;
    fontDescription.set_family("DS-Digital");
    fontDescription.set_size(25 * PANGO_SCALE);

    vbox.pack_start(grid, Gtk::PACK_SHRINK);

    Gtk::Box group1(Gtk::ORIENTATION_HORIZONTAL, 0); 

    Gtk::Label label1("Glucose");
    label1.set_size_request(450, 30);

    Pango::FontDescription fontDescription1;
    fontDescription1.set_family("DS-Digital");
    fontDescription1.set_size(50 * PANGO_SCALE);
    label1.override_font(fontDescription1);
    label1.override_background_color(Gdk::RGBA("#a8af7b"), Gtk::STATE_FLAG_NORMAL);

    Gtk::Label label1Number("120");
    label1Number.set_size_request(450, 150);  
    fontDescription1.set_size(100 * PANGO_SCALE);
    label1Number.override_font(fontDescription1);
    label1Number.override_background_color(Gdk::RGBA("#a8af7b"), Gtk::STATE_FLAG_NORMAL);

    group1.pack_start(label1, Gtk::PACK_SHRINK);
    group1.pack_start(label1Number, Gtk::PACK_SHRINK);

    Gtk::Box group2(Gtk::ORIENTATION_HORIZONTAL, 0);

    Gtk::Label label2("Insulin");
    label2.set_size_request(450, 30);  

    Pango::FontDescription fontDescription2;
    fontDescription2.set_family("DS-Digital");
    fontDescription2.set_size(50 * PANGO_SCALE);
    label2.override_font(fontDescription2);
    label2.override_background_color(Gdk::RGBA("#a8af7b"), Gtk::STATE_FLAG_NORMAL);

    Gtk::Label label2Number("0");
    label2Number.set_size_request(450, 150);
    fontDescription2.set_size(100 * PANGO_SCALE);
    label2Number.override_font(fontDescription2);
    label2Number.override_background_color(Gdk::RGBA("#a8af7b"), Gtk::STATE_FLAG_NORMAL);

    group2.pack_start(label2, Gtk::PACK_SHRINK);
    group2.pack_start(label2Number, Gtk::PACK_SHRINK);

    Gtk::Box group3(Gtk::ORIENTATION_HORIZONTAL, 0);

    Gtk::Label label3("Time");
    label3.set_size_request(450, 30);

    Pango::FontDescription fontDescription3;
    fontDescription3.set_family("DS-Digital");
    fontDescription3.set_size(50 * PANGO_SCALE);
    label3.override_font(fontDescription3);
    label3.override_background_color(Gdk::RGBA("#a8af7b"), Gtk::STATE_FLAG_NORMAL);

    Gtk::Label label3Number("12:00");
    label3Number.set_size_request(450, 150);  
    fontDescription3.set_size(100 * PANGO_SCALE);
    label3Number.override_font(fontDescription3);
    label3Number.override_background_color(Gdk::RGBA("#a8af7b"), Gtk::STATE_FLAG_NORMAL);

    group3.pack_start(label3, Gtk::PACK_SHRINK);
    group3.pack_start(label3Number, Gtk::PACK_SHRINK);

    vbox.pack_start(group1, Gtk::PACK_SHRINK);
    vbox.pack_start(group2, Gtk::PACK_SHRINK);
    vbox.pack_start(group3, Gtk::PACK_SHRINK);

    Gtk::Box group4(Gtk::ORIENTATION_HORIZONTAL, 0);

    Gtk::Label label4("Stato");
    label4.set_size_request(450, 30);

    Pango::FontDescription fontDescription4;
    fontDescription4.set_family("DS-Digital");
    fontDescription4.set_size(50 * PANGO_SCALE);
    label4.override_font(fontDescription4);
    label4.override_background_color(Gdk::RGBA("#a8af7b"), Gtk::STATE_FLAG_NORMAL);

    Gtk::Label label4Value("True");
    label4Value.set_size_request(450, 150);  
    fontDescription4.set_size(100 * PANGO_SCALE);
    label4Value.override_font(fontDescription4);
    label4Value.override_background_color(Gdk::RGBA("#a8af7b"), Gtk::STATE_FLAG_NORMAL);

    group4.pack_start(label4, Gtk::PACK_SHRINK);
    group4.pack_start(label4Value, Gtk::PACK_SHRINK);

    vbox.pack_start(group4, Gtk::PACK_SHRINK);

    window.add(vbox);

    std::thread redisThread(redisUpdate, &redisMutex, c2r, reply, gluc, comp_dose, time_str, delta_str);

    auto updateFunction = [&label1Number, &label2Number, &label3Number, &label4Value, &gluc, &comp_dose, &time_str, &delta_str, &redisMutex]() {
        if(redisMutex.try_lock()){
            label1Number.set_text(gluc);
            label2Number.set_text(comp_dose);
            label3Number.set_text(time_str); 
            label4Value.set_text(delta_str);
            redisMutex.unlock();
        }

        return true;
    };
    Glib::signal_timeout().connect(updateFunction, 1);

    window.show_all();

    return app->run(window);
}
