#include "Servo.h"
#include "Sonar.h"
#include "ADC.h"
#include "uart.h"
#include "WiFi.h"
#include "Math.h"


volatile uint32_t degreeForSend = 0;

static double maxDistance = 70.0;
static double minDistance = 5.0;
volatile uint32_t distanceSonar[182] = {};
volatile uint32_t objectsAngle[20] = {};
volatile double objectsWidth[20] = {};
volatile uint32_t objectDistance[20] = {};
volatile uint32_t numObject = 0;
volatile uint32_t arrposition =0;
volatile uint32_t errorCalc = 0;


//edge detection
volatile int firstEdge = -1;
volatile int secondEdge = -1;

volatile int ObjectState = 0;
//0 no object yet
//1 hit side of object
//2 past second side of object


void findSmallestObject(){
    int i;
    int smallest = 0;//initially set to first
    double widthSmallest = objectsWidth[0];//set width to first object
    for(i = 1; i < numObject; i++){
        if(objectsWidth[i] < objectsWidth[smallest]){
            smallest = i;
        }
    }
    //turn servo to point at smallest object
    setToDegree(objectsAngle[smallest]);
    //print results
    lcd_printf("Object:%u\n"
                        "Distance:%d\n"
                        "Width:%lf\n"
                        "Angle:%u", smallest,objectDistance[smallest],objectsWidth[smallest],objectsAngle[smallest]);

}
void addObject(int firstDegree, int secondDegree){
    int middle = (firstDegree + secondDegree)/2;
    objectsAngle[arrposition] = middle;

    int separation = (secondDegree - firstDegree);
    //objectsWidth[arrposition] =   sqrt((double)(distanceSonar[middle]*distanceSonar[middle]) + (double)(distanceSonar[middle]*distanceSonar[middle]) - (double)(2*distanceSonar[middle]*distanceSonar[middle])*cos((double)(separation * .0174533)));
    objectsWidth[arrposition] = 2 *(distanceSonar[middle])*tan((double)((separation/2)* .0174533));
    double realWidth = (distanceSonar[middle])*tan((double)(separation/2)* .0174533);
    double realDistance = distanceSonar[middle];

    objectDistance[arrposition] = distanceSonar[middle];
    if((objectsWidth[arrposition] >= 0.1) && (objectDistance[arrposition] <= 81)){//valid object
        arrposition++;
        numObject++;

    char buffer [100];
    sprintf(buffer, "Object:%d - "
            "Edges: %d, %d - "
            "middle distance: %lf - "
            "width:%lf\n\r", numObject, firstDegree, secondDegree, realDistance, objectsWidth[arrposition]);
    uart_sendStr(buffer);
    }
    return;

}


void detectObject(int degree, double distance){
    if(ObjectState == 0){
        if((distance >= minDistance) &&(distance <= maxDistance)){
            ObjectState =1;
            firstEdge = degree;
        }
    }
    if(ObjectState == 1){
        if((distance >= minDistance) &&(distance <= maxDistance)){
        secondEdge = degree;
        }
        else{
        ObjectState = 0;
        addObject(firstEdge, secondEdge);
        }
    }
}




void SweepServo (int degree){

   if(degreeForSend < 180){
       degreeForSend = buttonMove(degree,1);
   }
   else{
       //change if you want to sweep back
   }
}







int main(void){
    button_init();
    lcd_init();
    //devices init
    SERVO_INIT();
    PING_INIT();
    ADC_init();
    uart_init();

    //timer inits
    TIMER_INITSONAR();
    TIMER_INIT();

    //setup WiFi
    //set password for wifi



    unsigned int distanceCM = 0;
    double steps;
    char buffer [100];

    uint8_t go = button_getButton();
    uint8_t reset = 0;

    while(go != 6){
        go = button_getButton();
    }

    sprintf(buffer, "Degrees       IR Distance (cm)    Sonar Distance (cm)\n\r");
    uart_sendStr(buffer);
    while(1){
        distanceCM = ping_read();
        //setPulseByButton();
        steps = ADC_read();
        if(steps > maxDistance){
            steps = maxDistance + 1.0;
        }
        sprintf(buffer, "%-14u%-19.2lf%-20u\n\r",degreeForSend, steps, distanceCM);
        /*sprintf(buffer, "CM : %u"
                "\n\rIR READING: %.2lf"
                "\n\rDegree:%u\n\r", distanceCM, steps,degreeForSend);*/
        //lcd_printf("CM : %u\nIR READING: %.2lf", distanceCM, steps);
        uart_sendStr(buffer);

        //collect all sonar distances
        distanceSonar[degreeForSend] = distanceCM;
        //detect
        detectObject(degreeForSend, steps);

        lcd_printf("Objects:%u\n"
                                "DistanceS:%u\n"
                                "DistanceIR:%f\n"
                                "Angle:%u", numObject,distanceCM,steps,degreeForSend);
        timer_waitMillis(50);




        if(degreeForSend == 180){
                    findSmallestObject();
                    while(reset != 1){\
                        reset = button_getButton();
                        //busy loop to stop after done
                        //put return statement here
                    }
                    //reset
                    setToDegree(0);
                    numObject= 0;
                    arrposition = 0;
                    degreeForSend = 0;
                    reset = 0;
                    ObjectState = 0;
                    sprintf(buffer, "Degrees       IR Distance (cm)    Sonar Distance (cm)\n\r");
                    uart_sendStr(buffer);

                }
        else{//move servo 1 degree
            SweepServo(1);
            timer_waitMillis(50);

        }


            //lcd_printf("Objects:%u\nSmallest Object:%u, %f, %u", numObject,objectDistance[0],objectsWidth[0],objectsAngle[0]);
        }
    }


