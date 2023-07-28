//Final project
//Bug free
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int oct1 = 0, oct2 = 0, oct3 = 0, oct4 = 0;
int OCT1 = 0, OCT2 = 0, OCT3 = 0, OCT4 = 0;
int o1, o2, o3, o4, n, temp = 0;

//conveting string ip as numerical ip octet
int get_ip()
{
    char IP[15], a[3];
    char new1[3]={0}, new2[3]={0}, new3[3]={0}, new4[3]={0};

    //int OCT1 = 0, OCT2 = 0, OCT3 = 0, OCT4 = 0;
    int i, j=0, p, k1, k2, k3, l1, l2, l3, l4, str_len, temp1=0, temp2=0, temp3=0, temp4=0;

    printf("Enter IP: ");
    scanf("%s", IP);

    //string length
    str_len=strlen(IP);

    for(i = 0; i < 15; i++) {

        if(IP[i] == 46) {
            a[j] = i;
            j++;
        }
    }

    k1 = a[0];
    k2 = a[1];
    k3 = a[2];

    //difining the length
    l1 = k1;
    l2 = (k2-k1)-1;
    l3 = (k3-k2)-1;
    l4 = str_len - (k3+1);

    //preaparing first octet
    for(i = 0; i < k1; i++){
        p = (int)IP[i]-'0';
        new1[i] = p;
    }
    for(i = 0; i < l1; i++){
        temp1 = temp1*10 + new1[i];
    }
    OCT1 = temp1;
    //printf("First octet = %d\n", OCT1);

    //second octet
    for(i = k1+1, j=0; i < k2; i++, j++) {
        p = (int)IP[i]-'0';
        new2[j]=p;
    }

    for(i = 0; i < l2; i++){
        temp2 = temp2*10 + new2[i];
    }
    OCT2 = temp2;
    //printf("Second octet = %d\n", OCT2);


    //third octet
    for(i = k2+1, j = 0; i < k3; i++, j++) {
        p = (int)IP[i]-'0';
        new3[j] = p;
    }

    for(i = 0; i < l3; i++){
        temp3 = temp3*10 + new3[i];
    }
    OCT3 = temp3;
    //printf("Thired octet = %d\n", OCT3);

     //forth octet
    for(i = k3+1, j = 0; i < str_len; i++, j++) {
        p = (int)IP[i]-'0';
        new4[j] = p;
    }

    for(i = 0; i < l4; i++){
        temp4 = temp4*10 + new4[i];
    }
    OCT4 = temp4;
    //printf("Forth octet = %d\n", OCT4);
    printf("\n");
    return 0;
}

//Subnet mask
int subnet_mask()
{
    //int n , i = 0, j;
    int i = 0, j;
    int a[32] = {0}, a1[8] = {0}, a2[8] = {0}, a3[8] = {0}, a4[8] = {0};
    //int oct1 = 0, oct2 = 0, oct3 = 0, oct4 = 0;
    printf("Enter the value of \\n = ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        a[i] = 1;
    }

    for(i = 0, j = 0; i < 8; i++, j++) {
        a1[j] = a[i];
    }

    for(i = 8, j = 0; i < 16; i++, j++) {
        a2[j] = a[i];
    }

    for(i = 16, j = 0; i < 24; i++, j++) {
        a3[j] = a[i];
    }

    for(i = 24, j = 0; i < 32; i++, j++) {
        a4[j] = a[i];
    }

    //subnet mask

    //first octet
    for(i = 0, j = 7; i < 8; i++, j--) {
        oct1 = oct1 + a1[i]*(pow(2, j));
    }

    //second octet
    for(i = 0, j = 7; i < 8; i++, j--) {
        oct2 = oct2 + a2[i]*(pow(2, j));
    }


    //third octet
    for(i = 0, j = 7; i < 8; i++, j--) {
        oct3 = oct3 + a3[i]*(pow(2, j));
    }

    //Forth octet
    for(i = 0, j = 7; i < 8; i++, j--) {
        oct4 = oct4 + a4[i]*(pow(2, j));
    }

    printf("\nSubnet Mask: %d.%d.%d.%d\n", oct1,oct2,oct3,oct4);

    printf("\n");

    return 0;
}

int get_network_address()
{
    o1 = OCT1&oct1;
    o2 = OCT2&oct2;
    o3 = OCT3&oct3;
    o4 = OCT4&oct4;
    printf("Network Address: %d.%d.%d.%d\n", o1, o2, o3, o4);

    printf("\n");

    return 0;
}

int O4_octet()
{
    int a, x, t, broadcast_o4;
    x = 32 - n;
    if(x > 8){
        temp = x-8;
        broadcast_o4 = 255;
        t = o3 + temp;
        o3 = t;
    }
    else{
    a = pow(2, x);
    broadcast_o4 = a-1;
    }

    return broadcast_o4;
}

void host_adresses() {

    printf("First Assignable Host Address: %d.%d.%d.%d\n", o1, o2, o3, o4+1);
    int a = O4_octet();
    int x1 = 0, x2 = 0;
    x1 = a+o4;
    x2 = a+o4-1;
    //here is the bug
    //printf("a = %d\n", a);
    //bug has been removed
    printf("\nLast Assignable Host Address: %d.%d.%d.%d\n", o1, o2, o3, x2);
    printf("\nBroadcast Address: %d.%d.%d.%d\n", o1, o2, o3, x1);
    printf("\n");
}


void available_host() {
    int a, x;
    x = 32 - n;
    a = pow(2, x) - 2;
    printf("Available host number: %d\n", a);
}

int main()
{

    get_ip();
    subnet_mask();
    get_network_address();
    host_adresses();
    available_host();

    return 0;
}

