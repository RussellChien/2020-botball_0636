#include <kipr/wombat.h>
#include <drive.h>

//motors
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define CLAW 2

//servos
#define PUSHER 0
#define COMPRESSER

//sensors

//light values 
#define LIGHT 

//claw values
#define CLAW_OPEN 0
#define CLAW_CLOSE CLAW_OPEN + 500

//pusher values
#define PUSHER_DOWN 1980
#define PUSHER_START 0

//compresser values
#define COMPRESSER_UP 
#define COMPRESSER_DOWN 



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
}

void line_follow(int dist, int speed) { 
    drive(speed, speed);
    long leftTarg = gmpc(MOT_LEFT) + 150 * dist;
    long rightTarg = gmpc(MOT_RIGHT) + 150 * dist;
    while (gmpc(MOT_RIGHT) < rightTarg || gmpc(MOT_LEFT) < leftTarg) {
        if (analog(left_light) > black)
            drive(speed * .75, speed * 1.25);
        else if (analog(right_light) > black)
            drive(speed * 1.25, speed * .75);
        else
            drive(speed, speed);
        msleep(1);
    }
    ao();
}

void line_sense(int speed) {    
    drive(speed * SPD_L_F / MAX_SPEED, speed * SPD_R_F / MAX_SPEED);
    while (analog(left_light) < black || analog(right_light) < black) {
        if (analog(right_light) > black)
            drive(speed * SPD_L_F / MAX_SPEED, 0);
        else if (analog(left_light) > black)
            drive(0, speed * SPD_R_F / MAX_SPEED);
        else if (analog(left_light) <= black && analog(right_light) <= black)
            drive(speed, speed);
        msleep(1);
    }
    printf("black line sensed\n");
    ao();
} 
*/
void slow_servo(int port, int pos) {

    while(get_servo_position(port) > pos) {
        set_servo_position(port, get_servo_position(port)-5);
        msleep(8);
    }

    while(get_servo_position(port) < pos) {
        set_servo_position(port, get_servo_position(port)+5);
        msleep(8);
    }
}

/*void slow_servo(int port, int start, int end) {
    int i = 0;
    for(i; i < 30; i++) {
        start += (end - start)/30;
        set_servo_position(port, start);        
        msleep(100);
    }
}*/

void turn_left(int speed, int time){
    mav(MOT_LEFT, -speed);
    mav(MOT_RIGHT, speed);
    msleep(time);
    ao();
}

void turn_right(int speed, int time){
    mav(MOT_LEFT, speed);
    mav(MOT_RIGHT, -speed);
    msleep(time);
    ao();
}

/*void square_up(int speed, double change){
    while(left_touch == 0 && right_touch == 0){
        if(left_touch == 1){
            turn_right(-speed, 10);
        }
        else if(right_touch == 1){
            turn_left(-speed, 10);
        }
        move(-speed, 10, change);
    }
} */
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

int main(){
   
    enable_servos();    
    //starting positions
  	set_servo_position(PUSHER, PUSHER_START);
    //need to clear motor counter for claw
    //micro servo compressor 
    //start 
    //shut_down_in(119);
    
    //grabbing material transport 
    
    //pushing the titanium bin 
    set_servo_position(PUSHER, PUSHER_DOWN); 
    left(15, 0);
    forward(30);
    
    //moving into position under bridge to meet with create 
    

    
    
    
    
    return 0;

}
