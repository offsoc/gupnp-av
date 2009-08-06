/*
 * Copyright (C) 2009 Nokia Corporation.
 *
 * Authors: Zeeshan Ali (Khattak) <zeeshan.ali@nokia.com>
 *                                <zeeshanak@gnome.org>
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

/**
 * SECTION:gupnp-didl-lite-container
 * @short_description: DIDL-Lite Container
 *
 * #GUPnPDIDLLiteContainer respresents a DIDL-Lite container element.
 */

#include <string.h>

#include "gupnp-didl-lite-container.h"
#include "xml-util.h"

G_DEFINE_TYPE (GUPnPDIDLLiteContainer,
               gupnp_didl_lite_container,
               GUPNP_TYPE_DIDL_LITE_OBJECT);

enum {
        PROP_0,
        PROP_SEARCHABLE,
        PROP_CHILD_COUNT
};

static void
gupnp_didl_lite_container_init (GUPnPDIDLLiteContainer *container)
{
        /* Nothing to initialize, yay! */
}

static void
gupnp_didl_lite_container_get_property (GObject    *object,
                                        guint       property_id,
                                        GValue     *value,
                                        GParamSpec *pspec)
{
        GUPnPDIDLLiteContainer *container;

        container = GUPNP_DIDL_LITE_CONTAINER (object);

        switch (property_id) {
        case PROP_SEARCHABLE:
                g_value_set_boolean
                        (value,
                         gupnp_didl_lite_container_get_searchable (container));
                break;
        case PROP_CHILD_COUNT:
                g_value_set_uint
                        (value,
                         gupnp_didl_lite_container_get_child_count (container));
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
                break;
        }
}

static void
gupnp_didl_lite_container_class_init (GUPnPDIDLLiteContainerClass *klass)
{
        GObjectClass *object_class;

        object_class = G_OBJECT_CLASS (klass);

        object_class->get_property = gupnp_didl_lite_container_get_property;

        /**
         * GUPnPDIDLLiteContainer:searchable
         *
         * Whether this container is searchable.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_SEARCHABLE,
                 g_param_spec_boolean ("searchable",
                                       "Searchable",
                                       "Whether this container is searchable.",
                                       FALSE,
                                       G_PARAM_READABLE |
                                       G_PARAM_STATIC_NAME |
                                       G_PARAM_STATIC_NICK |
                                       G_PARAM_STATIC_BLURB));

        /**
         * GUPnPDIDLLiteContainer:child-count
         *
         * The child count of this container.
         **/
        g_object_class_install_property
                (object_class,
                 PROP_CHILD_COUNT,
                 g_param_spec_uint ("child-count",
                                    "ChildCount",
                                    "The child count of this container.",
                                    0,
                                    G_MAXUINT,
                                    0,
                                    G_PARAM_READABLE |
                                    G_PARAM_STATIC_NAME |
                                    G_PARAM_STATIC_NICK |
                                    G_PARAM_STATIC_BLURB));
}

/**
 * gupnp_didl_lite_container_get_searchable
 * @container: #GUPnPDIDLLiteContainer
 *
 * Checks whether @container is searchable.
 *
 * Return value: #TRUE if @container is searchable.
 **/
gboolean
gupnp_didl_lite_container_get_searchable (GUPnPDIDLLiteContainer *container)
{
        xmlNode *xml_node;

        g_return_val_if_fail (container != NULL, FALSE);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_CONTAINER (container), FALSE);

        xml_node = gupnp_didl_lite_object_get_xml_node
                                (GUPNP_DIDL_LITE_OBJECT (container));

        return xml_util_get_boolean_attribute (xml_node, "searchable");
}

/**
 * gupnp_didl_lite_container_get_child_count
 * @container: #GUPnPDIDLLiteContainer
 *
 * Get the child count of the @container.
 *
 * Return value: The child count of the @container.
 **/
guint
gupnp_didl_lite_container_get_child_count (GUPnPDIDLLiteContainer *container)
{
        xmlNode *xml_node;

        g_return_val_if_fail (container != NULL, 0);
        g_return_val_if_fail (GUPNP_IS_DIDL_LITE_CONTAINER (container), 0);

        xml_node = gupnp_didl_lite_object_get_xml_node
                                (GUPNP_DIDL_LITE_OBJECT (container));

        return xml_util_get_uint_attribute (xml_node, "childCount", 0);
}