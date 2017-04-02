/*
 * Copyright (C) 2014 Collabora Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Author: Jonny Lamb <jonny.lamb@collabora.co.uk>
 */


#include "panel.h"

struct MaynardPanelPrivate
{
  GtkWidget *system_button;
};

G_DEFINE_TYPE(MaynardPanel, maynard_panel, GTK_TYPE_WINDOW)

static void
maynard_panel_init (MaynardPanel *self)
{
	self->priv
	= G_TYPE_INSTANCE_GET_PRIVATE(self, MAYNARD_PANEL_TYPE, MaynardPanelPrivate);
}

static void print_hello()
{
	printf("kek\n");
}

static void
maynard_panel_constructed (GObject *object)
{
  MaynardPanel *self = MAYNARD_PANEL(object);
  GtkWidget *main_box;
  GtkWidget *label;

  G_OBJECT_CLASS (maynard_panel_parent_class)->constructed (object);

	/* window properties */
	gtk_window_set_title (GTK_WINDOW (self), "maynard");
	gtk_window_set_decorated (GTK_WINDOW (self), FALSE);
	gtk_widget_realize(GTK_WIDGET (self));

	/* make it black and slightly alpha */
	// gtk_style_context_add_class(gtk_widget_get_style_context (GTK_WIDGET (self)), "maynard-panel");

	/* main box */
	main_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_add (GTK_CONTAINER (self), main_box);

	label = gtk_label_new (":: CURRENT TIME %е ::");
	gtk_container_add (GTK_CONTAINER (main_box), label);

	GtkWidget *button;

	button = gtk_button_new_with_label ("Run...");
	g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
	g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), button);
	gtk_container_add (GTK_CONTAINER (main_box), button);
}

static void
maynard_panel_dispose (GObject *object)
{
  MaynardPanel *self = MAYNARD_PANEL (object);


  G_OBJECT_CLASS (maynard_panel_parent_class)->dispose (object);
}

static void
maynard_panel_class_init (MaynardPanelClass *klass)
{
  GObjectClass *object_class = (GObjectClass *)klass;
  GParamSpec *param_spec;

  object_class->constructed = maynard_panel_constructed;
  object_class->dispose = maynard_panel_dispose;

  g_type_class_add_private (object_class, sizeof (MaynardPanelPrivate));
}

GtkWidget *
maynard_panel_new (void)
{
  return g_object_new (MAYNARD_PANEL_TYPE, NULL);
}
