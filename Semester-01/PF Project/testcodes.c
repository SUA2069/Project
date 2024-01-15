#include <gtk/gtk.h>

void destroy_window(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(GTK_WIDGET(data)); // Destroy the window
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *button = gtk_button_new_with_label("Close Window");
    g_signal_connect(button, "clicked", G_CALLBACK(destroy_window), window);

    gtk_container_add(GTK_CONTAINER(window), button);
    
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}
