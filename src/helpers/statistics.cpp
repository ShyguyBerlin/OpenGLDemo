#include <helpers/statistics.h>

#include <stdio.h>
#include <GLFW/glfw3.h>

namespace helpers{

    int framecounter = 0;
    double prev_time = glfwGetTime();

    void fps_counter(){
        double curr_time = glfwGetTime();
        framecounter++;
        if(curr_time-prev_time >= 1.0){
            printf("%d fps \n",framecounter);
            framecounter = 0;
            prev_time = curr_time;
        }
    }

}