#include <gtkmm.h>
#include <iostream>
#include <random>

double getRandomNumber(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

void updateValues(Gtk::Label& label, double min, double max) {
    double randomValue = getRandomNumber(min, max);
    label.set_text(Glib::ustring::format(randomValue));
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

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

    Gtk::Label label2Number("80");
    label2Number.set_size_request(450, 150);
    fontDescription2.set_size(100 * PANGO_SCALE);
    label2Number.override_font(fontDescription2);
    label2Number.override_background_color(Gdk::RGBA("#a8af7b"), Gtk::STATE_FLAG_NORMAL);

    group2.pack_start(label2, Gtk::PACK_SHRINK);
    group2.pack_start(label2Number, Gtk::PACK_SHRINK);

    Gtk::Box group3(Gtk::ORIENTATION_VERTICAL, 0);

    Gtk::Image image1, image2;
    Glib::RefPtr<Gdk::Pixbuf> originalPixbuf1 = Gdk::Pixbuf::create_from_file("./icon.png");
    Glib::RefPtr<Gdk::Pixbuf> originalPixbuf2 = Gdk::Pixbuf::create_from_file("./heart.png");

    Glib::RefPtr<Gdk::Pixbuf> scaledPixbuf1 = originalPixbuf1->scale_simple(64, 64, Gdk::INTERP_BILINEAR);
    Glib::RefPtr<Gdk::Pixbuf> scaledPixbuf2 = originalPixbuf2->scale_simple(64, 64, Gdk::INTERP_BILINEAR);

    image1.set(scaledPixbuf1);
    image2.set(scaledPixbuf2);

    group3.pack_start(image1, Gtk::PACK_SHRINK);
    group3.pack_start(image2, Gtk::PACK_SHRINK);

    vbox.pack_start(group1, Gtk::PACK_SHRINK);
    vbox.pack_start(group2, Gtk::PACK_SHRINK);
    vbox.pack_start(group3, Gtk::PACK_SHRINK);

    window.add(vbox);

    auto updateFunction = [&label1Number, &label2Number, &image1, &image2]() {
        updateValues(label1Number, 80, 120);
        updateValues(label2Number, 60, 100);
        static bool isVisible1 = true;
        isVisible1 = !isVisible1;
        image1.set_visible(isVisible1);
        static bool isVisible2 = true;
        isVisible2 = !isVisible2;
        image2.set_visible(isVisible2);

        return true;
    };

    Glib::signal_timeout().connect(updateFunction, 1000);

    window.show_all();

    return app->run(window);
}
