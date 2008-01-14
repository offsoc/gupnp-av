/*
 * Copyright (C) 2008 OpenedHand Ltd.
 *
 * Authors: Jorn Baayen <jorn@openedhand.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <libgupnp-av/gupnp-search-criteria-parser.h>

static void
begin_parens_cb (GUPnPSearchCriteriaParser *parser,
                 gpointer                   user_data)
{
        g_print ("(");
}

static void
end_parens_cb (GUPnPSearchCriteriaParser *parser,
               gpointer                   user_data)
{
        g_print (")");
}

static void
conjunction_cb (GUPnPSearchCriteriaParser *parser,
                gpointer                   user_data)
{
        g_print (" and ");
}

static void
disjunction_cb (GUPnPSearchCriteriaParser *parser,
                gpointer                   user_data)
{
        g_print (" or ");
}

static void
expression_cb (GUPnPSearchCriteriaParser *parser,
               const char                *property,
               GUPnPSearchCriteriaOp      op,
               const char                *value,
               gpointer                   user_data)
{
        g_print ("%s %d %s", property, op, value);
}

int
main (int argc, char **argv)
{
        GUPnPSearchCriteriaParser *parser;
        GError *error;

        g_assert (argc == 2);

        g_type_init ();

        parser = gupnp_search_criteria_parser_new ();

        g_signal_connect (parser,
                          "begin_parens",
                          G_CALLBACK (begin_parens_cb),
                          NULL);
        g_signal_connect (parser,
                          "end_parens",
                          G_CALLBACK (end_parens_cb),
                          NULL);
        g_signal_connect (parser,
                          "conjunction",
                          G_CALLBACK (conjunction_cb),
                          NULL);
        g_signal_connect (parser,
                          "disjunction",
                          G_CALLBACK (disjunction_cb),
                          NULL);
        g_signal_connect (parser,
                          "expression",
                          G_CALLBACK (expression_cb),
                          NULL);

        error = NULL;
        gupnp_search_criteria_parser_parse_text (parser, argv[1], &error);
        if (error != NULL) {
                g_error (error->message);

                return 1;
        }

        g_print ("\n");

        return 0;
}