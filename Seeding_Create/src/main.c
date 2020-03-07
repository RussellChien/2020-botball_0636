#include <kipr/wombat.h>
#include "createDrive.h"

#define left_touch 1
#define right_touch 0

//sensor ports

//sensor values 

//servo ports
#define wrist 1
#define arm 0

//effector values 
#define arm_vert 1470
#define arm_horz 265
#define arm_down 180
#define arm_back 2470

#define wrist_horz 193
#define wrist_vert 1320
#define wrist_dump 1756

void set_up(){
    enable_servos();
    create_connect();
    create_full();
    printf("connected");
    //calc_dev();
    set_servo_position(arm, arm_back);
    msleep(500);
    set_servo_position(wrist, wrist_horz);
    msleep(500);
    //shut_down_in(119);
}

void grab_basket(){
    
 	//GRAB AND DUMP BASKET
    
    
   	printf("getting basket\n");

    set_servo_position(arm, arm_horz);	
    msleep(5);
    set_servo_position(wrist, wrist_horz);
    msleep(5);
    printf("arm in position\n");

	create_square_up_cliff(-100);
    printf("squared up complete\n");
    
    msleep(100);
    
    create_forward(31, 100);
 	printf("hooked basket\n");   
    
    msleep(200);

	servo_slow(arm, arm_horz+400);
    msleep(5);
    printf("basket lifted\n");
    
	create_backward(20, 100);
    printf("basket dragged out");
    
    create_square_up_cliff(-100);
  
    
    servo_slow(arm, arm_horz);
    msleep(5);  
    printf("basket set down\n");
    
    while(!side_button()) msleep(1);
    
	servo_slow(arm, arm_horz+400);
    msleep(5);
    printf("basket lifted\n");
    
    while(!side_button()) msleep(1);
	
    
	servo_slow(wrist, wrist_vert);
    msleep(5);
    printf("dumped partly\n");
    int i = 0;
    for(i = 0; i<3; i++){
    	servo_slow(arm, arm_horz+400);
    	servo_slow(arm, arm_horz+300);
    }
    
    while(!side_button()) msleep(1);
    servo_slow(wrist, wrist_dump);
    msleep(5);
    printf("dumped full\n");
    for(i = 0; i<3; i++){
    	servo_slow(arm, arm_horz+400);
    	servo_slow(arm, arm_horz+300);
    }
    create_disconnect();
}

void square_buttons(int speed){
    if(left_touch == 0 && right_touch == 0){
        create_drive_direct(speed, speed);
    }else if(left_touch == 1 && right_touch == 0){
        create_drive_direct( 0, speed);
    }else if(left_touch == 0 && right_touch == 1){
        create_drive_direct(speed, 0);
    }
}

void forward_until_bump(int speed){
	while(!get_create_lbump() || !get_create_rbump()) create_drive_direct(speed, speed);
}   

int main(){
    int i;
   	create_connect();
    enable_servos();
    create_full();
    create_skip_cliff();
    
  /*	set_up();
    
    while(!side_button()) msleep(1);
    
    set_servo_position(arm, arm_vert);
   	
    
 	create_forward(50, 100);
    msleep(10000);
    create_backward(5, 100);
    //moves forward toward mine carts 
    create_forward(50, 250);
    create_left(90, 250);
    //squares up against the back 
    create_backward(20, 100);
    //moves forward to the second yellow cube
    create_forward(25, 250);
    //turns toward second yellow cube 
    create_right(90, 250);
    //pushes yellow cube out 
    create_forward(20, 250);
    create_forward(20, -250);
    create_left(90, 250);
    //moves toward third yellow cube 
    create_forward(25, 250);
    create_right(90, 250);
    create_forward(20, 250);
    //can push the minecarts back if need room for claw 
    create_forward(10, -250);
    create_right(135, 250);
    create_left(225, 250);
    create_forward(15, -250);
    //otherwise when pulling basket it will push the mine carts back
    //turns towards basket of titantium poms 
    create_left(45, 250);
    create_forward(15, 250);
    //grabs it using some effector (to be built)
    //slow servo or set servo position?
    //drags it out
    create_forward(30, -250);
    //lifts effector out 
    //squares up on middle black line
    //moves forward to grab basket of titantium poms
    //lifts basket up and out
    //??? and dumps poms into funnel 
    
    //create gets arm 
    
 //   return 0;
    
    set_servo_position(arm, arm_horz);
    msleep(5);
    set_servo_position(wrist, wrist_horz);
    msleep(5);
    
    //create is in position to push away mine carts, facing the ravine
    create_right(45, 100);
    create_left(45, 100); */
    
    //start
    
    servo_slow(arm, arm_horz);
    msleep(5);
    servo_slow(wrist, wrist_vert);
    msleep(5);
    
    create_square_up_cliff(100);
    msleep(5);
    
    create_forward(30, 100);
    
    servo_slow(arm, arm_horz+100);
    msleep(5);
    
    create_forward(30, 100);
    msleep(10);
    
    while(!side_button()) msleep(1);
    
    create_backward(20, 100);
    
	create_square_up_cliff(-100);
    
    //go to next cube
    create_left(90, 100);
    create_forward(30, 100);
    create_right(90, 100);
    
    create_disconnect();
    
    return 0;
    
}



