#include <gst/gst.h>

int main(int argc, char *argv[]) {
    GstElement *pipeline, *source, *sink;

    gst_init(&argc, &argv);


    source = gst_element_factory_make("videotestsrc", "source");
    sink = gst_element_factory_make("autovideosink", "sink");


    pipeline = gst_pipeline_new("test-pipeline");

    if (!pipeline || !source || !sink) {
        g_printerr("Not all elements could be created.\n");
        return -1;
    }


    gst_bin_add_many(GST_BIN(pipeline), source, sink, NULL);


    if (gst_element_link(source, sink) != TRUE) {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(pipeline);
        return -1;
    }


    gst_element_set_state(pipeline, GST_STATE_PLAYING);


    GstBus *bus = gst_element_get_bus(pipeline);
    gst_bus_poll(bus, GST_MESSAGE_EOS, GST_CLOCK_TIME_NONE);
    gst_object_unref(bus);


    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;


//gcc play_videotest.c -o play_videotest.out `pkg-config --cflags --libs gstreamer-1.0`

}
