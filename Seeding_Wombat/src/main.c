#include <kipr/wombat.h>
#include <drive.h>

//servos
#define PUSHER 0
#define CLAW 1
#define COMPRESSOR 2
#define GRABBER 3

//digital sensors
#define LEFT_TOUCH 0 
#define RIGHT_TOUCH 1

//analog sensors 
#define LEFT_LIGHT 0
#define RIGHT_LIGHT 1

//light values 
#define LIGHT 
#define WHITE 2500
#define BLACK 3700

//claw values
#define CLAW_OPEN 1200
#define CLAW_CLOSE 0

//pusher values
#define PUSHER_DOWN 1925
#define PUSHER_START 0

//grabber values
#define GRABBER_UP 1385
#define GRABBER_DOWN 500

//compressor values 


/*
void updateCam(){
    camData[1] = camera_update();
    camData[2] = get_object_count(burning);
    if(camData[2] > 0){
        camData[3] = get_object_center_x(burning, camData[2]-1);
        camData[4] = get_object_center_y(burning, camData[2]-1);
        printf("Camera Update: %d, Objects: %d, x: %d, y: %d ", camData[1], camData[2], camData[3], camData[4]); 
    }
    else{
        printf("Camera Update: %d, Objects: %d ", camData[1], camData[2]);  
    }
}

void openCam(){
    int open = camera_open_black();
    if(open == 1){
        printf("Successfully opened\n");
    }
    else{
        printf("Failed to open\n");
        //openCam();
    }
}

int findObject(){
    int i, objects, final, av = 0;  

    for(i = 1; i <= 35; i++){
        updateCam();
        printf("EMPTY\n");
    }

    for(i = 1; i <= 20; i++){
        updateCam();
        objects = camData[2];
        if(objects > 0){
            printf("Item detected\n");
            final++;
            av = av + objects;
        }
        else{
            printf("Item not detected\n");
        }
        msleep(20);
    }
    if(final > 0){
        av = av/final;
    }
    else{
        av = 0;
    }
    printf("Successes: %d, Average: %d\n", final, av);

    if(final >= 15){
        return 1;
    }
    else{
        return 0;
    }
}*/

void line_follow(int dist, int speed) { 
    drive(speed, speed);
    long leftTarg = gmpc(MOT_LEFT) + 150 * dist;
    long rightTarg = gmpc(MOT_RIGHT) + 150 * dist;
    while (gmpc(MOT_RIGHT) < rightTarg || gmpc(MOT_LEFT) < leftTarg) {
        if (analog(LEFT_LIGHT) > BLACK)
            drive(speed * .75, speed * 1.25);
        else if (analog(LEFT_LIGHT) < BLACK)
            drive(speed * 1.25, speed * .75);
        else
            drive(speed, speed);
        msleep(1);
    }
    ao();
}

void line_sense(int speed) {    
    int i;
    int left_black = 0;
    int right_black = 0;
    for(i = 0; i < 10; i++) {
    	left_black += analog(LEFT_LIGHT);
    	right_black += analog(RIGHT_LIGHT);
    }
    left_black /= 10;
    right_black /= 10;
    left_black += 400;
    right_black += 400;
    drive(speed * SPD_L_F / MAX_SPEED, speed * SPD_R_F / MAX_SPEED);
    while (analog(LEFT_LIGHT) < left_black || analog(RIGHT_LIGHT) < right_black) {
        if (analog(LEFT_LIGHT) > left_black) {
            drive(0, speed * SPD_R_F / MAX_SPEED);
        }
        else if (analog(RIGHT_LIGHT) > right_black) {
            drive(speed * SPD_L_F / MAX_SPEED, 0);
        }
        else if (analog(LEFT_LIGHT) <= left_black && analog(RIGHT_LIGHT) <= right_black) {
            drive(speed, speed);
        }
        msleep(1);
    }
    printf("black line sensed\n");
   	mav(MOT_LEFT, -15);
    msleep(20);
    freeze(MOT_LEFT);
    freeze(MOT_RIGHT);
    ao();
} 


void slow_servo(int port, int dest)
{
    int pos = get_servo_position(port);
    if (dest > pos) 
    {
        while (pos < dest) 
        {
            pos += 1;
            set_servo_position(port, pos);
            msleep(1);
        }
    }
    else
    {
        while (pos > dest) 
        {
            pos -= 1;
            set_servo_position(port, pos);
            msleep(1);
        }
    }
}


/*void light_start(){
    while(right_button());
    int max = 0,
    min = 9999,
    curr = 0,
    avg = 0;
    display_clear();
    display_printf(0,0,"Max:");
    display_printf(0,1,"Min:");
    display_printf(0,2,"Curr:");
    display_printf(0,3,"avg:");
    while (!right_button()) {
        curr = analog(LIGHT);

        if (curr > max) max = curr;
        if (curr < min) min = curr;

        avg = (max + min) / 2;

        display_printf(5, 0, "%d   ", max);
        display_printf(5, 1, "%d   ", min);
        display_printf(6, 2, "%d   ", curr);
        display_printf(5,3,"%d   ",avg);

        if (curr > avg) display_printf(10,5,"XX");
        else display_printf(10,5,"OO");

        msleep(50);
    }
    msleep(1000);
    display_clear();
    display_printf(0,4,"Prepared to begin: left to skip");

    while (analog(LIGHT) > avg && !(right_button())) 
        msleep(50);
} */

void grab_transport() {
    forward(18); 
    msleep(1000);
    set_servo_position(GRABBER, GRABBER_DOWN);
    msleep(1000);
    backward_speed(35, 1000); 
    set_servo_position(GRABBER, GRABBER_UP);
    forward(10);
    set_servo_position(CLAW, CLAW_CLOSE);
    set_servo_position(GRABBER, GRABBER_DOWN);
    msleep(1000);
}

void push_bin() {
    set_servo_position(PUSHER, PUSHER_DOWN);     
    left(10, 0);
    backward_speed(50, 1000);
    right(10, 0);
    backward_speed(30, 1000);
}


int main() {
   
    enable_servos();    
    //starting positions
    set_servo_position(PUSHER, PUSHER_START);
    set_servo_position(CLAW, CLAW_OPEN);
    set_servo_position(GRABBER, GRABBER_UP);
    
    //shut_down_in(119);
    //starts with claw facing forward
    square_up(1000);
    msleep(500);
    line_sense(1250); 
    msleep(1000);
    backward(3);
    msleep(1000);
    right(90, 0);
    msleep(1000);
    forward(5);
    line_sense(750);
    msleep(1000);
    //grabbing material transport 
    grab_transport();
    backward(20);
    square_up(1000);
    msleep(1000);
    forward(15);
    msleep(1000);
    //turns toward bin 
    right(90, 0);
    msleep(1000);
    //pushing the titanium bin 
    push_bin();
    forward(50); 
    msleep(1000);
    set_servo_position(PUSHER, PUSHER_START);
    msleep(1000);
	line_sense(1000);
    msleep(1000);
    
   
    //moving into position under bridge to meet with create 
    
    //disable_servos();
    
    return 0;

}
