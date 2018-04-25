#include <gtk/gtk.h>
typedef struct
{
        GSList *windows;
        
        /* etc... whatever application vars you need */
} MyApp;
void 
on_window_destroy (GtkWidget *widget, MyApp *app)
{
        app->windows = g_slist_remove (app->windows, widget);
        
        if (g_slist_length (app->windows) == 0)
        {
                /* last window was closed... exit */
                
                g_debug ("Exiting...");
                g_slist_free (app->windows);
                gtk_main_quit ();
        }
}
GtkWidget *g_lbl_hello;
GtkWidget *g_lbl_count;
void myCSS(void);
void on_add_button_clicked (GtkWidget *widget, MyApp *app);
int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
    gtk_init(&argc, &argv);
     myCSS();

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_window_fullscreen(GTK_WINDOW(window));
    // get pointers to the two labels
    g_lbl_hello = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_time_o111"));
    g_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_status_o111"));
 
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}
 
// called when button is clicked
void on_btn_hello_clicked()
{
    // printf("on_btn_hello_clicked\n");
    // static unsigned int count = 0;
    // char str_count[30] = {0};
    
    // gtk_label_set_text(GTK_LABEL(g_lbl_hello), "Tgian: 00:03:04");
    // count++;
    // sprintf(str_count, "%d", count);
    // gtk_label_set_text(GTK_LABEL(g_lbl_count), str_count);
        MyApp *app;
        app = g_slice_new (MyApp);
        app->windows = NULL;
        
        /* create first window */
        on_add_button_clicked (NULL, app);
}
 
// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

void myCSS(void){
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "css/mystyle.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}

void
on_add_button_clicked (GtkWidget *widget, MyApp *app)
{
      
    GtkBuilder      *builder; 
    GtkWidget       *window;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_setup.glade", NULL);
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    // get pointers to the two labels
    g_lbl_hello = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_time_o111"));
    g_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_status_o111"));
    
    g_object_unref(builder);
    
    gtk_widget_show(window);                
    gtk_main();
}