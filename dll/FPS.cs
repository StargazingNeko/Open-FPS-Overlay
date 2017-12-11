using System;
using System.Collections.Generic;
using System.Text;

namespace Open_FPS_Overlay
{
    public class FPS
    {
        private static int startTime;
        private static int endTime;
        private static int frameTimes = 0;
        private static short frames = 0;

    // Start counting the fps
    public static void StartCounter()
        {
            //get the current time
            int startTime = (int)TimeSpan.TicksPerMillisecond;
        }

        //stop counting the fps and display it at the 
        public static void StopAndPost()
        {
        //get the current time
        int endTime = (int)TimeSpan.TicksPerMillisecond;
            //the difference between start and end times
            frameTimes = frameTimes + endTime - startTime;
        //count one frame
        frames++;
        //if the difference is greater than 1 second (or 1000ms) post the results
        if(frameTimes >= 1000)
        {
                //post results at the console
                Console.WriteLine(frames.ToString());
                //reset time differences and number of counted frames
                frames = 0;
                frameTimes = 0;
        }
    }
}
}
