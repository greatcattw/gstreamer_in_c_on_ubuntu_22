#include <gst/gst.h>

int main(int argc, char *argv[]) {
    GstElement *pipeline, *source, *capsfilter, *jpegdec, *videoconvert, *sink;
    GstBus *bus;
    GstMessage *msg;


    gst_init(&argc, &argv);


    source = gst_element_factory_make("v4l2src", "source"); 
    capsfilter = gst_element_factory_make("capsfilter", "capsfilter"); 
    jpegdec = gst_element_factory_make("jpegdec", "jpegdec");
    videoconvert = gst_element_factory_make("videoconvert", "converter");
    //sink = gst_element_factory_make("autovideosink", "sink"); 
    sink = gst_element_factory_make("ximagesink", "sink"); 


    pipeline = gst_pipeline_new("camera-pipeline");

    if (!pipeline || !source || !capsfilter || !jpegdec || !videoconvert || !sink) {
        g_printerr("err1.\n");
        return -1;
    }


    g_object_set(source, "device", "/dev/video0", NULL); // ³]©w USB ÄáŒvŸ÷³]³Æ
    g_object_set(sink,"window-width",640,NULL);
    g_object_set(sink,"window-height",480,NULL);

/*
    GstCaps *caps = gst_caps_new_simple("video/x-raw",
    					//"format",G_TYPE_STRING,"MJPG",
    					"format",G_TYPE_STRING,"YUY2",
                                         "width", G_TYPE_INT, 640,
                                         "height", G_TYPE_INT, 480,
                                         "framerate", GST_TYPE_FRACTION,30,1,
                                         NULL);
*/
    GstCaps *caps = gst_caps_new_simple(//"video/x-raw",
    					"image/jpeg",
    					"format",G_TYPE_STRING,"MJPG",
                                         "width", G_TYPE_INT, 640,
                                         "height", G_TYPE_INT, 480,
                                         "framerate", GST_TYPE_FRACTION,30,1,
                                         NULL);                                         
    g_object_set(capsfilter, "caps", caps, NULL);
    gst_caps_unref(caps);


/*
    gst_bin_add_many(GST_BIN(pipeline), source, capsfilter, jpegdec, videoconvert, sink, NULL);

    if (gst_element_link(source, capsfilter) != TRUE ||
        gst_element_link(capsfilter, jpegdec) != TRUE ||
        gst_element_link(jpegdec, videoconvert) != TRUE ||
        gst_element_link(videoconvert, sink) != TRUE ) {
        g_printerr("err2.\n");
        gst_object_unref(pipeline);
        return -1;
    }
*/

//gst-launch-1.0  v4l2src device=/dev/video0 ! image/jpeg,format=MJPG,width=640,width=640,height=480,framerate=30/1 ! jpegdec ! ximagesink

    gst_bin_add_many(GST_BIN(pipeline), source, capsfilter, jpegdec, sink, NULL);

    if (gst_element_link(source, capsfilter) != TRUE ||
        gst_element_link(capsfilter, jpegdec) != TRUE ||
        gst_element_link(jpegdec, sink) != TRUE ) {
        g_printerr("err2.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    gst_element_set_state(pipeline, GST_STATE_PLAYING);


    bus = gst_element_get_bus(pipeline);
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);


    if (msg != NULL) {
        GError *err;
        switch (GST_MESSAGE_TYPE(msg)) {
            case GST_MESSAGE_ERROR:
                gst_message_parse_error(msg, &err, NULL);
                g_printerr("err5: %s\n", err->message);
                g_error_free(err);
                break;
            case GST_MESSAGE_EOS:
                g_print("err3.\n");
                break;
            default:
                g_printerr("err4.\n");
                break;
        }
        gst_message_unref(msg);
    }


    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
	
	//gcc usbcam_640x480_mjpg.c -o usbcam_640x480_mjpg.out `pkg-config --cflags --libs gstreamer-1.0`

}
