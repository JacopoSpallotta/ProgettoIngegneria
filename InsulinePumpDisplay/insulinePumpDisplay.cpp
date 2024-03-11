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

void getPersonalInfo(std::string& name, int& age, double& weight, std::string& gender, double& height) {
    Gtk::Dialog dialog("Inserisci le informazioni personali", true);
    dialog.set_default_size(300, 200);

    Gtk::Box* contentArea = dialog.get_content_area();

    Gtk::Label label_name("Nome:");
    Gtk::Entry entry_name;
    contentArea->pack_start(label_name, Gtk::PACK_SHRINK);
    contentArea->pack_start(entry_name, Gtk::PACK_SHRINK);

    Gtk::Label label_age("Età:");
    Gtk::SpinButton spin_age;
    spin_age.set_range(0, 120); // Imposta un limite ragionevole per l'età
    contentArea->pack_start(label_age, Gtk::PACK_SHRINK);
    contentArea->pack_start(spin_age, Gtk::PACK_SHRINK);

    Gtk::Label label_weight("Peso:");
    Gtk::SpinButton spin_weight;
    spin_weight.set_range(0, 500); // Imposta un limite ragionevole per il peso
    contentArea->pack_start(label_weight, Gtk::PACK_SHRINK);
    contentArea->pack_start(spin_weight, Gtk::PACK_SHRINK);

    Gtk::Label label_gender("Sesso:");
    Gtk::ComboBoxText combo_gender;
    combo_gender.append("Maschio");
    combo_gender.append("Femmina");
    contentArea->pack_start(label_gender, Gtk::PACK_SHRINK);
    contentArea->pack_start(combo_gender, Gtk::PACK_SHRINK);

    Gtk::Label label_height("Altezza (cm):");
    Gtk::SpinButton spin_height;
    spin_height.set_range(0, 300); // Imposta un limite ragionevole per l'altezza
    contentArea->pack_start(label_height, Gtk::PACK_SHRINK);
    contentArea->pack_start(spin_height, Gtk::PACK_SHRINK);

    dialog.add_button("OK", Gtk::RESPONSE_OK);
    dialog.show_all();

    int result = dialog.run();

    if (result == Gtk::RESPONSE_OK) {
        name = entry_name.get_text();
        age = static_cast<int>(spin_age.get_value());
        weight = spin_weight.get_value();
        gender = combo_gender.get_active_text();
        height = spin_height.get_value();
    }
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    std::string name, gender;
    int age;
    double weight, height;
    getPersonalInfo(name, age, weight, gender, height);

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

    // Creazione delle etichette per visualizzare le informazioni personali
    Pango::FontDescription fontDescription;
    fontDescription.set_family("DS-Digital");
    fontDescription.set_size(25 * PANGO_SCALE);

Gtk::Label label_name(name);
label_name.override_font(fontDescription);
label_name.override_color(Gdk::RGBA("#a8af7b"));
grid.attach(label_name, 0, 0);

Gtk::Label label_gender(gender);
label_gender.override_font(fontDescription);
label_gender.override_color(Gdk::RGBA("#a8af7b"));
grid.attach(label_gender, 3, 0);

Gtk::Label label_age(std::to_string(age) + " yo");
label_age.override_font(fontDescription);
label_age.override_color(Gdk::RGBA("#a8af7b"));
grid.attach(label_age, 1, 0);

Gtk::Label label_weight(std::to_string(static_cast<int>(weight)) + " Kg");  // Conversione a intero
label_weight.override_font(fontDescription);
label_weight.override_color(Gdk::RGBA("#a8af7b"));
grid.attach(label_weight, 2, 0);


Gtk::Label label_height(std::to_string(static_cast<int>(height)) + " cm");  // Conversione a intero
label_height.override_font(fontDescription);
label_height.override_color(Gdk::RGBA("#a8af7b"));
grid.attach(label_height, 4, 0);

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

    Gtk::Label label3("Values");
    label3.set_size_request(900, 30); 

    Pango::FontDescription fontDescription3;
    fontDescription3.set_family("DS-Digital");
    fontDescription3.set_size(25 * PANGO_SCALE);
    label3.override_font(fontDescription3);
    label3.override_background_color(Gdk::RGBA("#a8af7b"), Gtk::STATE_FLAG_NORMAL);

    Gtk::Label label3Number("G     t     Qsto     EGP     Uid     E     ISR");
    label3Number.set_size_request(900, 150);  
    fontDescription3.set_size(30 * PANGO_SCALE); 
    label3Number.override_font(fontDescription3);
    label3Number.override_background_color(Gdk::RGBA("#a8af7b"), Gtk::STATE_FLAG_NORMAL);

    group3.pack_start(label3, Gtk::PACK_SHRINK);
    group3.pack_start(label3Number, Gtk::PACK_SHRINK);

    // Aggiunta delle immagini lampeggianti con dimensioni ridotte
    Gtk::Image image1, image2;
    Glib::RefPtr<Gdk::Pixbuf> originalPixbuf1 = Gdk::Pixbuf::create_from_file("./icon.png");
    Glib::RefPtr<Gdk::Pixbuf> originalPixbuf2 = Gdk::Pixbuf::create_from_file("./heart.png");

    // Imposta le dimensioni desiderate (ad esempio, 16x16)
    Glib::RefPtr<Gdk::Pixbuf> scaledPixbuf1 = originalPixbuf1->scale_simple(64, 64, Gdk::INTERP_BILINEAR);
    Glib::RefPtr<Gdk::Pixbuf> scaledPixbuf2 = originalPixbuf2->scale_simple(64, 64, Gdk::INTERP_BILINEAR);

    image1.set(scaledPixbuf1);
    image2.set(scaledPixbuf2);

    group3.pack_start(image1, Gtk::PACK_SHRINK);
    group3.pack_start(image2, Gtk::PACK_SHRINK);

    // Aggiunta delle etichette alla finestra

    vbox.pack_start(group1, Gtk::PACK_SHRINK);
    vbox.pack_start(group2, Gtk::PACK_SHRINK);
    vbox.pack_start(group3, Gtk::PACK_SHRINK);

    window.add(vbox);

    // Funzione di aggiornamento che verrà chiamata ogni secondo
    auto updateFunction = [&label1Number, &label2Number, &image1, &image2]() {
       updateValues(label1Number, 80, 120); // Imposta i valori desiderati per glucosio
        updateValues(label2Number, 60, 100); // Imposta i valori desiderati per insulina

        // Alternare la visibilità delle immagini (lampeggiamento)
        static bool isVisible1 = true;
       isVisible1 = !isVisible1;
        image1.set_visible(isVisible1);
        static bool isVisible2 = true;
        isVisible2 = !isVisible2;
        image2.set_visible(isVisible2);

        return true; // Continua a chiamare questa funzione
    };

    // Chiamata a updateFunction ogni 1000 millisecondi (1 secondo)
    Glib::signal_timeout().connect(updateFunction, 1000);

    window.show_all();

    return app->run(window);
}
