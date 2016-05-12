/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/*
 * Copyright 2009 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 * Boston, MA 02111-1307, USA.
 *
 */
#include <stdlib.h>
#include <stdio.h>

#include <glib-2.0/glib.h>

#include <clutter/clutter.h>
#include <mx/mx.h>

static ClutterScript *script = NULL;

int
main (int argc, char *argv[])
{
  GObject *stage;
  GError *error = NULL;
  gint res;

  clutter_init (&argc, &argv);

  /* load the style sheet */
  mx_style_load_from_file (mx_style_get_default (),
                             "style/default.css", NULL);

  script = clutter_script_new ();
  g_assert (CLUTTER_IS_SCRIPT (script));

  clutter_script_load_from_file (script, "test-script.json", &error);
  if (error)
    {
      g_print ("*** Error:\n"
               "***   %s\n", error->message);
      g_error_free (error);
      g_object_unref (script);
      return EXIT_FAILURE;
    }

  clutter_script_connect_signals (script, NULL);

  res = clutter_script_get_objects (script,
                                    "main-stage", &stage,
                                    NULL);

  clutter_actor_show (CLUTTER_ACTOR (stage));

  clutter_main ();

  g_object_unref (script);

  return EXIT_SUCCESS;
}
