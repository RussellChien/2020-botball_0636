#include <kipr/wombat.h>
#include "createDrive.h"\


//sensor ports

//sensor values 

//servo ports

//effector values 

int main(){
    enable_servos();
    create_connect();
    create_full();
    printf("connected");

    //start 
    //shut_down_in(119);
    create_square_up_gyro(500, 250);
    //moves forward toward mine carts 
    create_forward_gyro_dist(50, 250);
    create_left(90, 250);
    //squares up against the back 
    create_square_up_gyro(500, 250);
    //moves forward to the second yellow cube
    create_forward_gyro_dist(25, 250);
    //turns toward second yellow cube 
    create_right(90, 250);
    //pushes yellow cube out 
    create_forward_gyro_dist(20, 250);
    create_forward_gyro_dist(20, -250);
    create_left(90, 250);
    //moves toward third yellow cube 
    create_forward_gyro_dist(25, 250);
    create_right(90, 250);
    create_forward_gyro_dist(20, 250);
    //can push the minecarts back if need room for claw 
    create_forward_gyro_dist(10, -250);
    create_right(135, 250);
    create_left(225, 250);
    create_forward_gyro_dist(15, -250);
    //otherwise when pulling basket it will push the mine carts back
    //turns towards basket of titantium poms 
    create_left(45, 250);
	create_forward_gyro_dist(15, 250);
    //grabs it using some effector (to be built)
    //slow servo or set servo position?
    //drags it out
    create_forward_gyro_dist(30, -250);
    //lifts effector out 
    //squares up on middle black line
    //moves forward to grab basket of titantium poms
    //lifts basket up and out
    //??? and dumps poms into funnel
    






    create_disconnect();

    return 0;
}
