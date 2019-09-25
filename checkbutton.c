#include <gtk/gtk.h>

gulong handler_id;

void load_css ( void );
GtkWidget *createWindow ( const gint width, const gint height );
GtkWidget *createGrid   ( const guint border, gboolean row_homogeneous, gboolean column_homogeneous, guint row_spacing, guint column_spacing );
void toggled_callback   ( GtkToggleButton *checked_button, gpointer button );
void clicked_callback   ( GtkWidget *button  );

int main ( int argc, char *argv[] )
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *check_Button;
    GtkWidget *button;
    gtk_init ( &argc, &argv );
    load_css();
    window = createWindow ( 400, 300 );
    /// ***
    grid = createGrid ( 3, FALSE, FALSE, 3, 3 );
    gtk_container_add ( GTK_CONTAINER ( window ), grid );
    /// ***
    /// check_Button = gtk_check_button_new();
    /// check_Button = gtk_check_button_new_with_label( "_Check the Button to Quit" );
    check_Button = gtk_check_button_new_with_mnemonic ( "_Check the Button to Quit" );
    /// ***
    button = gtk_button_new_with_label ( "Quit" );
    /// ***
    handler_id = g_signal_connect ( check_Button, "toggled", G_CALLBACK ( toggled_callback ), button );
    if ( handler_id  != 0 )
    {
        g_signal_connect_swapped ( button, "clicked", G_CALLBACK ( clicked_callback ), button );
    }

    /// ***
    gtk_grid_attach ( GTK_GRID ( grid ), check_Button,  0, 0, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( grid ), button,        0, 1, 1, 1 );
    /// ***
    gtk_widget_show_all ( window );
    gtk_main();
}

void load_css ( void )
{
    GtkCssProvider *provider;
    GdkDisplay     *display;
    GdkScreen      *screen;
    /// ***
    const gchar *css_style_file = "style.css";
    GFile *css_fp               = g_file_new_for_path ( css_style_file );
    GError *error               = 0;
    /// ***
    provider = gtk_css_provider_new ();
    display  = gdk_display_get_default ();
    screen   = gdk_display_get_default_screen ( display );
    /// ***
    gtk_style_context_add_provider_for_screen   ( screen, GTK_STYLE_PROVIDER ( provider ), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION );
    gtk_css_provider_load_from_file             ( provider, css_fp, &error );
    /// ***
    g_object_unref ( provider );
}

GtkWidget *createWindow ( const gint width, const gint height )
{
    GtkWidget *window = gtk_window_new  ( GTK_WINDOW_TOPLEVEL );
    g_signal_connect        ( window, "destroy", gtk_main_quit, window );
    gtk_window_set_default_size ( GTK_WINDOW ( window ), width, height );
    gtk_container_set_border_width  ( GTK_CONTAINER ( window ), 25 );
    return window;
}

GtkWidget *createGrid ( const guint border, gboolean row_homogeneous, gboolean column_homogeneous, guint row_spacing, guint column_spacing )
{
    GtkWidget *grid = gtk_grid_new  ();
    gtk_grid_set_row_homogeneous    ( GTK_GRID ( grid ), row_homogeneous );
    gtk_grid_set_column_homogeneous ( GTK_GRID ( grid ), column_homogeneous );
    /// ***
    gtk_grid_set_row_spacing        ( GTK_GRID ( grid ), row_spacing );
    gtk_grid_set_column_spacing     ( GTK_GRID ( grid ), column_spacing );
    ///***
    gtk_container_set_border_width  ( GTK_CONTAINER ( grid ), border );
    g_object_set                    ( grid, "tooltip-text", "Grid", NULL );
    return grid;
}

void toggled_callback ( GtkToggleButton *checked_button, gpointer button )
{
    if ( gtk_toggle_button_get_active ( checked_button ) )
    {
        handler_id = g_signal_connect( button, "clicked", gtk_main_quit, NULL );
    }
    else
    {
        g_signal_handler_disconnect( button, handler_id );
    }
}

void clicked_callback ( GtkWidget *button  )
{
    ( void ) button;
    static gulong temp;

    if ( temp == 0 )
    {
        temp = handler_id;
    }

    if ( temp == handler_id )
    {
        g_print("Please check the box\n" );
    }
    else
    {
        g_print( "GoodBye\n" );
    }
}
