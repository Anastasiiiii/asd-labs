#include<windows.h>
#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#define pi 3.14159265358979323846

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[]="Лабораторна робота 4(1 частина)";


double** randm(int rows, int cols){
                double** matrix = (double**)malloc(rows * sizeof(double*));

                for (int i = 0; i < rows; i++)
                    matrix[i] = (double*)malloc(cols * sizeof(double));

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        matrix[i][j] =  2.0 * rand()/RAND_MAX;
                    }
                }
                return matrix;
    }

double** mulmr(double coef, double **matrix, int rows, int cols){
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        matrix[i][j] = matrix[i][j] * coef;
                        if(matrix[i][j] > 1.0) {
                            matrix[i][j] = 1;
                        } else matrix[i][j] = 0;
                        }
                }
                return matrix;
    }


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS w;
    w.lpszClassName=ProgName;
    w.hInstance=hInstance;
    w.lpfnWndProc=WndProc;
    w.hCursor=LoadCursor(NULL, IDC_ARROW);
    w.hIcon=0;
    w.lpszMenuName=0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style=CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;
    hWnd=CreateWindow(ProgName,
        "Lab3. Fartushnyak Anastasia IP-04",
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        1400,
        1500,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&lpMsg, hWnd, 0, 0)) {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
    return(lpMsg.wParam);
    }

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
    {
    HDC hdc;
    PAINTSTRUCT ps;

    void arrow(float fi, int px,int py){
            fi = 3.1416 *(180.0 - fi)/180.0;
            int lx,ly,rx,ry;
            px = px - 20 * cos(fi);
            py = py - 20 * sin(fi);
            lx = px-15*cos(fi+0.3);
            rx = px-15*cos(fi-0.3);
            ly = py-15*sin(fi+0.3);
            ry = py-15*sin(fi-0.3);
            MoveToEx(hdc, lx, ly, NULL);
            LineTo(hdc, px, py);
            LineTo(hdc, rx, ry);
            return 0;
      }

    switch(messg){
        case WM_PAINT :
            hdc=BeginPaint(hWnd, &ps);
            char *nn[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
            int nx[12] = {100, 200, 800};
            int ny[12] = {100, 100, 100};
            int i, dx = 20, dy = 20, dtx = 5;
            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(175, 36, 36));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
            SelectObject(hdc, KPen);



        srand(0425);
        double** T = randm(12, 12);
        double coef = 1 - 2*0.02 - 5*0.005 - 0.25;
        double** A = mulmr(coef, T, 12, 12);
        double B[12][12];
//directed graf

        for(int i = 0; i < 12; i++) {
            if(i == 0) {
                nx[i] = 50;
                ny[i] = 225;
            } else if(i < 5) {
                nx[i] = nx[i - 1] + 50;
                ny[i] = ny[i - 1] - 50;
            } else if(i < 9) {
                nx[i] = nx[i - 1] + 50;
                ny[i] = ny[i - 1] + 50;
            } else {
                nx[i] = nx[i - 1] - 100;
                ny[i] = ny[i - 1];
            }
        }



        printf("Matrix for directed graf\n");
            for (int i = 0; i < 12; i++) {
                for (int j = 0; j < 12; j++) {
                    printf("%g ", A[i][j]);
                }
                printf("\n");}
            int nx0, ny0, R;
            int nxs, nys;
            double k, m;
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){
                    if (A[i][j] == 1){
                            if (i == j)
                            {
                             Arc(hdc, nx[j], ny[j], nx[j] + 40, ny[j] + 40, nx[j], ny[j], nx[j], ny[j]);
                             arrow(-7, nx[j], ny[j]);
                             continue;
                            }
                            if  ((A[j][i]==1) && (i>j)) {
                              nxs = (nx[i] + nx[j])/2 - (ny[i]-ny[j])/6;
                              nys = (ny[i] + ny[j])/2 - (nx[i] - nx[j])/6;
                              MoveToEx (hdc, nx[j], ny[j], NULL);
                              LineTo (hdc, nxs, nys);
                              MoveToEx (hdc, nxs, nys, NULL);
                              LineTo (hdc, nx[i], ny[i]);
                              R = (pow(nx[i] - nx0, 2) + pow(ny[i] - ny0, 2))/sqrt(3);
                              k = atan2(ny[j] - ny[i], nx[j] - nx[i]);
                              m = atan2(sqrt(pow(nx[j] - nx[i], 2) + pow(ny[j] - ny[i], 2)), R/2);
                              arrow((260 - (260/pi*(m + k))), nx[j], ny[j]);
                              continue;
                            }
                            if ((i <= 4) && (j <= 4))
                            {
                              nxs = (nx[i] + nx[j])/2.6 - (ny[i] - ny[j])/6;
                              nys = (ny[i] + ny[j])/2.6 - (nx[i] - nx[j])/6;
                              MoveToEx (hdc, nx[j], ny[j], NULL);
                              LineTo (hdc, nxs, nys);
                              MoveToEx (hdc, nxs, nys, NULL);
                              LineTo (hdc, nx[i], ny[i]);
                              R = (pow(nx[i] - nx0, 2) + pow(ny[i] - ny0, 2))/sqrt(3);
                              k = atan2(ny[j] - ny[i], nx[j] - nx[i]);
                              m = atan2(sqrt(pow(nx[j] - nx[i], 2) + pow(ny[j] - ny[i], 2)), R/2);
                              arrow((280 - (240/pi*(m + k))), nx[j], ny[j]);
                              continue;
                            }
                            if ((i >= 4) && (i <= 8) && (j >= 4) && (j <= 8))
                            {
                              nxs = (nx[i] + nx[j])/1.7 - (ny[i]-ny[j])/6;
                              nys = (ny[i] + ny[j])/2.6 - (nx[i] - nx[j])/6;
                              MoveToEx (hdc, nx[j], ny[j], NULL);
                              LineTo (hdc, nxs, nys);
                              MoveToEx (hdc, nxs, nys, NULL);
                              LineTo (hdc, nx[i], ny[i]);
                              R = (pow(nx[i] - nx0, 2) + pow(ny[i] - ny0, 2))/sqrt(3);
                              k = atan2(ny[j] - ny[i], nx[j] - nx[i]);
                              m = atan2(sqrt(pow(nx[j] - nx[i], 2) + pow(ny[j] - ny[i], 2)), R/2);
                              arrow((180 - (100/pi*(m + k))), nx[j], ny[j]);
                              continue;
                            }
                            if (((i==0) && (j==11))||((i==11) && (j==0))||(i==j+1)||(i==j-1)) {
                                MoveToEx(hdc, nx[i], ny[i], NULL);
                                LineTo(hdc, nx[j], ny[j]);
                                arrow(-7, nx[j], ny[j]);
                                continue;
                            }
                            if (((i >= 8) || (i == 0)) && ((j >= 8) || (j == 0)))
                            {
                              nxs = (nx[i] + nx[j])/1.6 - (ny[i] - ny[j])/6;
                              nys = (ny[i] + ny[j])/1.6 - (nx[i] - nx[j])/6;
                              MoveToEx (hdc, nx[j], ny[j], NULL);
                              LineTo (hdc, nxs, nys);
                              MoveToEx (hdc, nxs, nys, NULL);
                              LineTo (hdc, nx[i], ny[i]);
                              R = (pow(nx[i] - nx0, 2) + pow(ny[i] - ny0, 2))/sqrt(3);
                              k = atan2(ny[j] - ny[i], nx[j] - nx[i]);
                              m = atan2(sqrt(pow(nx[j] - nx[i], 2) + pow(ny[j] - ny[i], 2)), R/2);
                              arrow((360 - (340/pi*(m + k))), nx[j], ny[j]);
                            }
                            MoveToEx(hdc, nx[i], ny[i], NULL);
                            LineTo(hdc, nx[j], ny[j]);
                            arrow((180 - (290/pi*(m + k))), nx[j], ny[j]);
                            }
                            }
                            }
                            for (int i = 0; i < 12; i++)
                        {
                        for(int j = 0; j < 12; j++)
                        {
                        Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
                        TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2,  nn[i], 2);
                        }
                        }
                        int deg_pl[12]={0,0,0,0,0,0,0,0,0,0,0,0}, deg_mi[12]={0,0,0,0,0,0,0,0,0,0,0,0};
                        char text[15];
                        for(i=0;i < 12;i++){
                        for(int j=0;j < 12;j++){
                        deg_pl[i]+=A[i][j];
                    sprintf_s(text, 13, "deg(+)%d= %d", i+1, deg_pl[i]);
                    TextOutA(hdc, nx[i]-70 -dtx,ny[i]+70-dy/2, text, 12);
                    deg_mi[i]+=A[j][i];
                    sprintf_s(text, 13, "deg(-)%d= %d", i+1, deg_mi[i]);
                    TextOutA(hdc, nx[i]+20-dtx,ny[i]+35-dy/2, text, 13);
                }
            }


            // Non-directed

            for(int i = 0; i < 12; i++) {
            if(i == 0) {
                nx[i] = 50;
                ny[i] = 600;
            } else if(i < 5) {
                nx[i] = nx[i - 1] + 50;
                ny[i] = ny[i - 1] - 50;
            } else if(i < 9) {
                nx[i] = nx[i - 1] + 50;
                ny[i] = ny[i - 1] + 50;
            } else {
                nx[i] = nx[i - 1] - 100;
                ny[i] = ny[i - 1];
            }
        }


         printf("Matrix for non-directed graph\n");
            for (int i = 0; i < 12; i++) {
                for (int j = 0; j < 12; j++) {
                    if (j < i) {
                        B[i][j] =  A[j][i];
                    }
                    else {
                        B[i][j] =  A[i][j];
                    }
                    printf("%g ", B[i][j]);
                }
                printf("\n");
            }
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){
                    if (B[i][j] == 1){
                             if (i == j)
                            {
                              Arc(hdc, nx[j], ny[j], nx[j] + 40, ny[j] + 40, nx[j], ny[j], nx[j], ny[j]);
                              MoveToEx(hdc, nx[i], ny[i], NULL);
                              LineTo(hdc, nx[j], ny[j]);
                              continue;
                            }


                            if ((i <= 4) && (j <= 4))
                            {
                              nxs = (nx[i] + nx[j])/2.3 - (ny[i] - ny[j])/8;
                              nys = (ny[i] + ny[j])/2.3 - (nx[i] - nx[j])/8;
                              MoveToEx (hdc, nx[j], ny[j], NULL);
                              LineTo (hdc, nxs, nys);
                              MoveToEx (hdc, nxs, nys, NULL);
                              LineTo (hdc, nx[i], ny[i]);
                              continue;
                            }
                            if ((i >= 4) && (i <= 8) && (j >= 4) && (j <= 8))
                            {
                              nxs = (nx[i] + nx[j])/1.7 - (ny[i]-ny[j])/6;
                              nys = (ny[i] + ny[j])/2.6 - (nx[i] - nx[j])/6;
                              MoveToEx (hdc, nx[j], ny[j], NULL);
                              LineTo (hdc, nxs, nys);
                              MoveToEx (hdc, nxs, nys, NULL);
                              LineTo (hdc, nx[i], ny[i]);
                              continue;
                            }
                            if (((i==0) && (j==11))||((i==11) && (j==0))||(i==j+1)||(i==j-1)) {
                                MoveToEx(hdc, nx[i], ny[i], NULL);
                                LineTo(hdc, nx[j], ny[j]);
                                continue;
                            }
                            if (((i >= 8) || (i == 0)) && ((j >= 8) || (j == 0)))
                            {
                              nxs = (nx[i] + nx[j])/2.6 - (ny[i] - ny[j])/9;
                              nys = (ny[i] + ny[j])/2.6 - (nx[i] - nx[j])/9;
                              MoveToEx (hdc, nx[j], ny[j], NULL);
                              LineTo (hdc, nxs, nys);
                              MoveToEx (hdc, nxs, nys, NULL);
                              LineTo (hdc, nx[i], ny[i]);

                            }
                            MoveToEx(hdc, nx[i], ny[i], NULL);
                            LineTo(hdc, nx[j], ny[j]);
                            }
                            }
                            }

                            for (int i = 0; i < 12; i++)
                        {
                        for(int j = 0; j < 12; j++)
                        {
                        Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
                        TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2,  nn[i], 2);
                        }
                        }

                        int stepNenap[12] = {};
                        printf("\nStepeni non-directed graf:\n");
                        for ( int i = 0; i < 12; i++ ) stepNenap[i] = 0;
                        for ( int i = 0; i < 12; i++ ) {
                            for ( int j = 0; j < 12; j++ ) {
                                if ( B[i][j] == 1 ) {
                                    stepNenap[i]++;
                                }
                                    if ( (B[i][j] == 1) && (B[j][i] == 1) && ( i == j) ) {
                                    stepNenap[i]++;
                                }
                            }
                            printf("%i  ",stepNenap[i]);
                        }
                        printf("\n");
                        int stepNap[12][2] = {};
                        for ( int i = 0; i < 12; i++ ) {
                            stepNap[i][0] = 0;
                            stepNap[i][1] = 0;
                        }
                        for ( int i = 0; i < 12; i++ ) {
                            for ( int j = 0; j < 12; j++ ) {
                                if ( A[i][j] == 1 ) {
                                    stepNap[i][0]++;
                                    stepNap[j][1]++;
                                }
                            }
                        }
                        printf("\nStepeni directed graf:");
                        printf("\ndeg+\tdeg-\n");

                        for ( int i = 0; i < 12; i++ ) {
                            printf( "%i\t%i\n", stepNap[i][0], stepNap[i][1] );
                        }
                        int deg[12]={0,0,0,0,0,0,0,0,0,0,0};
                        for(i=0;i < 12;i++){
                            for(int j=0;j < 12;j++){
                                if (i==j) {
                                    deg[i]+=2*B[i][j];
                                }
                                else {
                                    deg[i]+=B[i][j];
                                }
                                sprintf_s(text, 9, "deg%d= %d", i+1, deg[i]);
                                TextOutA(hdc, nx[i]+20-dtx,ny[i]+20-dy/2, text, 9);
                            }
                        }

                        printf( "There is no isolated and hanging vertex\n" );
                        printf("Graf isn`t odnoridnuy\n");
                        char flag[12]="Однорідний";
                        for(i=0;i < 12;i++){
                        if (i!=0 && deg[i]!=deg[i-1]) {strcpy(flag, "Hеоднорідний");
                        } }
                        TextOut(hdc, 500,400, flag, 12);
                        printf("Shlyah 2\n");
                        double C[12][12];
                        for(i=0;i < 12;i++){
                            for(int j=0;j < 12;j++){
                                C[i][j]=0;
                                for(int k=0;k < 12;k++){
                                    C[i][j]=C[i][j]+A[i][k]*A[k][j];
                                }
                                if (C[i][j]>0) {
                            C[i][j]=1;
                            for(int k=0;k < 12;k++){
                                if (A[i][k]==1 && A[k][j]==1) {
                                    printf("%d->%d->%d || ", i+1, k+1, j+1);
                                }
                                }
                                }
                                }
                        }
                        printf("Shlyah3\n");
                        double D[12][12];
                        for(i=0;i < 12;i++){
                            for(int j=0;j < 12;j++){
                                D[i][j]=0;
                                for(int k=0;k < 12;k++){
                                    D[i][j]=D[i][j]+C[i][k]*A[k][j];
                                }
                                if (D[i][j]>0) {
                        for(int k=0;k < 12;k++){
                            if (C[i][k]==1 && A[k][j]==1) {
                                for(int m=0;m < 12;m++){
                                    if (A[i][m]==1 && A[m][k]==1) {
                                        D[i][j]=1;
                                         printf("%d->%d->%d->%d || ", i+1, k+1, j+1);
                                }
                                }
                                }
                                }
                                }
                                }
                        }
                       EndPaint(hWnd, &ps);

                        break;

                        case WM_DESTROY:
                        PostQuitMessage(0);
                        break;

                    default:
                        return(DefWindowProc(hWnd, messg, wParam, lParam));
                }
                return 0;
            }
