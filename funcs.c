#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

// Clear input buffer to remove extra characters
void clear_input_buffer(void){int c; while((c=getchar())!='\n' && c!=EOF); } 

// Ask user to go back, clear screen or exit
void back_clear_exit(void){
    char ch;
    printf("\nB - Back | C - Clear screen | E - Exit : ");
    scanf(" %c",&ch); clear_input_buffer();
    if(ch=='C'||ch=='c'){ system("clear"); printf("Screen cleared.\n"); }
    if(ch=='E'||ch=='e'){ printf("Exiting program...\n"); exit(0); }
}

// Get float value from user with prompt
float get_value(char *prompt){
    float val; 
    printf("%s",prompt); 
    scanf("%f",&val); 
    clear_input_buffer(); 
    return val;
}

// Calculate Voltage, Current or Resistance
void calc_VIR(float knownV,float knownI,float knownR,char type){
    if(type=='V'||type=='v') printf("Voltage = I * R = %.2f * %.2f = %.2f V\n",knownI,knownR,knownI*knownR);
    else if(type=='I'||type=='i') printf("Current = V / R = %.2f / %.2f = %.2f A\n",knownV,knownR,knownV/knownR);
    else if(type=='R'||type=='r') printf("Resistance = V / I = %.2f / %.2f = %.2f Ohms\n",knownV,knownI,knownV/knownI);
}

// Calculate voltage, current, or resistance for single resistor
void per_resistor_calc(float arr[],int n,float total_current,float total_voltage,int series){
    char choice; 
    printf("Do you want to calculate across a specific resistor? (Y/N): ");
    scanf(" %c",&choice); clear_input_buffer();
    if(choice!='Y' && choice!='y') return;

    int res_num; char type;
    printf("Which resistor (1-%d)? ",n); scanf("%d",&res_num); clear_input_buffer();
    if(res_num<1 || res_num>n){ printf("Invalid resistor number!\n"); return; }

    printf("Calculate Voltage (V), Current (I), or Resistance (R)? Enter V/I/R: ");
    scanf(" %c",&type); clear_input_buffer();

    float val = arr[res_num-1];

    if(series){ // Series circuit
        if(type=='V'||type=='v') 
            printf("Voltage across R%d = I_total * R%d = %.2f * %.2f = %.2f V\n",res_num,res_num,total_current,val,total_current*val);
        else if(type=='I'||type=='i') 
            printf("Current through R%d = I_total = %.2f A\n",res_num,total_current);
        else if(type=='R'||type=='r'){ 
            float knownV = get_value("Enter Voltage across resistor: "); 
            calc_VIR(knownV,total_current,val,'R'); 
        }
    } else { // Parallel circuit
        if(type=='V'||type=='v') 
            printf("Voltage across R%d = V_total = %.2f V\n",res_num,total_voltage);
        else if(type=='I'||type=='i') 
            printf("Current through R%d = V_total / R%d = %.2f / %.2f = %.2f A\n",res_num,res_num,total_voltage,val,total_voltage/val);
        else if(type=='R'||type=='r'){ 
            float knownV = get_value("Enter Voltage across resistor: "); 
            calc_VIR(knownV,total_voltage/val,val,'R'); 
        }
    }
}

// Menu 1: Calculate voltage
void menu_item_1(void){
    printf("\n--- Voltage Calculation ---\n");
    float I = get_value("Enter Current (A): "); 
    float R = get_value("Enter Resistance (Ohms): ");
    calc_VIR(0,I,R,'V'); 
    back_clear_exit();
}

// Menu 2: Calculate current
void menu_item_2(void){
    printf("\n--- Current Calculation ---\n");
    float V = get_value("Enter Voltage (V): "); 
    float R = get_value("Enter Resistance (Ohms): ");
    calc_VIR(V,0,R,'I'); 
    back_clear_exit();
}

// Menu 3: Calculate resistance
void menu_item_3(void){
    printf("\n--- Resistance Calculation ---\n");
    float V = get_value("Enter Voltage (V): "); 
    float I = get_value("Enter Current (A): ");
    calc_VIR(V,I,0,'R'); 
    back_clear_exit();
}

// Menu 4: Series circuit calculation
void menu_item_4(void){
    int n,i; 
    do {
        printf("\n--- Series Circuit (up to 10 resistors) ---\nHow many resistors? "); 
        scanf("%d",&n); clear_input_buffer();
        if(n>10 || n<1) printf("Invalid error! Please re-enter resistor numbers (1-10).\n");
    } while(n>10 || n<1);

    float r[10],total=0; 
    for(i=0;i<n;i++){ 
        char buf[20]; 
        snprintf(buf,20,"Enter R%d (Ohms): ",i+1); 
        r[i]=get_value(buf); 
        total+=r[i]; 
    }

    float V=get_value("Enter Supply Voltage (V): "); 
    float I=V/total; 
    float P=V*I;

    printf("\nTotal Resistance = %.2f Ohms\nTotal Current = %.2f A\nTotal Power = %.2f W\n",total,I,P);
    per_resistor_calc(r,n,I,V,1); 
    back_clear_exit();
}

// Menu 5: Parallel circuit calculation
void menu_item_5(void){
    int n,i; 
    do {
        printf("\n--- Parallel Circuit (up to 10 resistors) ---\nHow many resistors? "); 
        scanf("%d",&n); clear_input_buffer();
        if(n>10 || n<1) printf("Invalid error! Please re-enter resistor numbers (1-10).\n");
    } while(n>10 || n<1);

    float r[10],sum=0; 
    for(i=0;i<n;i++){ 
        char buf[20]; 
        snprintf(buf,20,"Enter R%d (Ohms): ",i+1); 
        r[i]=get_value(buf); 
        sum+=1/r[i]; 
    }

    float totalR = 1/sum; 
    float V=get_value("Enter Supply Voltage (V): "); 
    float I=V/totalR; 
    float P=V*I;

    printf("\nTotal Resistance = %.2f Ohms\nTotal Current = %.2f A\nTotal Power = %.2f W\n",totalR,I,P);
    per_resistor_calc(r,n,I,V,0); 
    back_clear_exit();
}

// Menu 6: Mixed circuit calculation
void menu_item_6(void){
    int s,p,i; 
    do {
        printf("\n--- Mixed Circuit ---\nNumber of series resistors (max 5): "); 
        scanf("%d",&s); clear_input_buffer();
        if(s>5 || s<1) printf("Invalid error! Please re-enter series resistor numbers (1-5).\n");
    } while(s>5 || s<1);

    float series[5],total_series=0; 
    for(i=0;i<s;i++){ 
        char buf[20]; 
        snprintf(buf,20,"Series R%d: ",i+1); 
        series[i]=get_value(buf); 
        total_series+=series[i]; 
    }

    do {
        printf("Number of parallel resistors (max 5): "); 
        scanf("%d",&p); clear_input_buffer();
        if(p>5 || p<1) printf("Invalid error! Please re-enter parallel resistor numbers (1-5).\n");
    } while(p>5 || p<1);

    float parallel[5],sum=0; 
    for(i=0;i<p;i++){ 
        char buf[20]; 
        snprintf(buf,20,"Parallel R%d: ",i+1); 
        parallel[i]=get_value(buf); 
        sum+=1/parallel[i]; 
    }

    float parallelR=sum>0?1/sum:0; 
    float totalR=total_series+parallelR; 
    float V=get_value("Enter Supply Voltage (V): "); 
    float I=V/totalR; 
    float P=V*I;

    printf("\nTotal Resistance = %.2f Ohms\nTotal Current = %.2f A\nTotal Power = %.2f W\n",totalR,I,P);

    char choice; 
    printf("Calculate across a resistor? (Y/N): "); 
    scanf(" %c",&choice); clear_input_buffer();

    if(choice=='Y'||choice=='y'){ 
        char type,grp; 
        int res; 
        printf("V/I/R? "); scanf(" %c",&type); clear_input_buffer();
        printf("Series or Parallel resistor? (S/P): "); scanf(" %c",&grp); clear_input_buffer(); 
        printf("Which resistor? "); scanf("%d",&res); clear_input_buffer();
        if(grp=='S'||grp=='s') per_resistor_calc(series,s,I,V,1); 
        else per_resistor_calc(parallel,p,I,V,0);
    }

    back_clear_exit();
}

// Menu 7: Power calculation
void menu_item_7(void){
    printf("\n--- Power Calculation ---\n"); 
    float V=get_value("Enter Voltage (V): "); 
    float I=get_value("Enter Current (A): ");
    printf("Power = %.2f W\n",V*I); 
    back_clear_exit();
}