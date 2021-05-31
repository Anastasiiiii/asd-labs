#include<windows.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
#include<math.h>
#define pi 3.14159265358979323846
char text[20];
int dx = 16, dy = 16, dtx = 5;
int W[12][12] = {0,};
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

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[]="Лабараторна робота 6";


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
        "ЛР 6. Виконала Легенька Ю.Д.",
        WS_OVERLAPPEDWINDOW,
        300,
        100,
        1200,
        800,
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

      void linesOfGraph(HDC hdc, int B[12][12], int *nx, int *ny, int i, int j, int tW) {
    int nx0, ny0, nxs, nys, R, oR, nxS, nyS;
    if (i>j) return;
    if (i == j){
        Arc(hdc, nx[j], ny[j], nx[j] + 40, ny[j] + 40, nx[j], ny[j], nx[j], ny[j]);
        if (tW) Rectangle(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
        sprintf_s(text, 3, "%d", B[i][j]);
        TextOut(hdc, nx[i]-6*dtx, ny[i]-2*dy,  text, 3);
        return;
    }
    if (((i==0) && (j==11))||((i==11) && (j==0))||(i==j+1)||(i==j-1)) {
         MoveToEx(hdc, nx[i], ny[i], NULL);
        LineTo(hdc, nx[j], ny[j]);
        if (tW) Rectangle(hdc, (nx[i]+nx[j])/2-dx,(ny[i]+ny[j])/2-dy,(nx[i]+nx[j])/2+dx,(ny[i]+ny[j])/2+dy);
        sprintf_s(text, 3, "%d", B[i][j]);
        TextOut(hdc, (nx[i]+nx[j])/2-dtx,(ny[i]+ny[j])/2-dy/2,  text, 3);
        return;
    }
    if ((i < 4) && ((j < 4))) {
        MoveToEx(hdc, nx[i], ny[i], NULL);
        LineTo(hdc, nx[j], ny[j]);
        if (tW) Rectangle(hdc, (nx[i]+nx[j])/2-dx,(ny[i]+ny[j])/2-dy,(nx[i]+nx[j])/2+dx,(ny[i]+ny[j])/2+dy);
        sprintf_s(text, 3, "%d", B[i][j]);
        TextOut(hdc, (nx[i]+nx[j])/2-dtx,(ny[i]+ny[j])/2-dy/2,  text, 3);
        return;
    }
    if ((i>=4) && (i < 8) && (j>=4) && (j < 8)){
        MoveToEx(hdc, nx[i], ny[i], NULL);
        LineTo(hdc, nx[j], ny[j]);
        if (tW) Rectangle(hdc, (nx[i]+nx[j])/2-dx,(ny[i]+ny[j])/2-dy,(nx[i]+nx[j])/2+dx,(ny[i]+ny[j])/2+dy);
        sprintf_s(text, 3, "%d", B[i][j]);
        TextOut(hdc, (nx[i]+nx[j])/2-dtx,(ny[i]+ny[j])/2-dy/2,  text, 3);
        return;
    }
    if (((i >= 8) || (i == 0)) && ((j >= 8) || (j == 0))) {
        nxs = (nx[i] + nx[j])/1.8- (ny[i] - ny[j])/8;;
        nys = (ny[i] + ny[j])/1.8 - (nx[i] - nx[j])/8;
        R = (pow(nx[i] - nx0, 2) + pow(ny[i] - ny0, 2))/sqrt(3);
        Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
        nxS=(nx[i]+nx[j])/2;
        nyS=(ny[i]+ny[j])/2;
        oR=sqrt(pow(nxS-nx0, 2) + pow(nyS-ny0, 2));
        if (tW) Rectangle(hdc, nx0-(nx0-nxS)*R/oR-dx,ny0-(ny0-nyS)*R/oR-dy,nx0-(nx0-nxS)*R/oR+dx,ny0-(ny0-nyS)*R/oR+dy);
        sprintf_s(text, 3, "%d", B[i][j]);
        TextOut(hdc, nx0-(nx0-nxS)*R/oR-dtx,ny0-(ny0-nyS)*R/oR-dy/2,  text, 3);
        return;
    }
    MoveToEx(hdc, nx[i], ny[i], NULL);
    LineTo(hdc, nx[j], ny[j]);
    if (tW) Rectangle(hdc, (nx[i]+nx[j])/2-dx,(ny[i]+ny[j])/2-dy,(nx[i]+nx[j])/2+dx,(ny[i]+ny[j])/2+dy);
    sprintf_s(text, 3, "%d", B[i][j]);
    TextOut(hdc, (nx[i]+nx[j])/2-dtx,(ny[i]+ny[j])/2-dy/2,  text, 3);
}
     void vertexOfGraph(HDC hdc, int nx[12], int ny[12], char* numVerticle[12], int n) {
     int dx = 16, dy = 16, dtx = 5;
     Ellipse(hdc, nx[n]-dx,ny[n]-dy,nx[n]+dx,ny[n]+dy);
     TextOut(hdc, nx[n]-dtx,ny[n]-dy/2,  numVerticle[n], 2);
    }

         void linesWeight(HDC hdc, int matrix[12][12], int nx[12], int ny[12], int i, int j){
        char text[1];
        sprintf_s(text, sizeof(text)+2, "%d", matrix[i][j]);
      if (matrix[i][j]>0) {
        if (i == j) {
            MoveToEx(hdc, nx[j], ny[j], NULL);
            TextOutA(hdc, nx[j] -30, ny[j] - 45, text, 3);
        } else {
           MoveToEx(hdc, nx[i], ny[i], NULL);
           TextOutA(hdc, (nx[i] + nx[j]) * 0.5-9, (ny[i] + ny[j]) * 0.5-9, text, 3);
        }
    }

    }

int algorythmPrima(int W[12][12],int nx[12], int ny[12],char* numVerticle[12]){
  int matrixofTree[12][12]={};
  int vertNum;
  int currentVert[12];
  int allWeights[12];
  memset (currentVert, false, sizeof (currentVert));
  vertNum = 0;
  currentVert[0] = true;

  int first=0;
  int last=0;
  int sum=0;
  while (vertNum < 12 - 1) {

      int min = 9999999;

      for (int i = 0; i < 12; i++) {
        if (currentVert[i]) {
            for (int j = 0; j < 12; j++) {
              if (W[i][j] && !currentVert[j]) {
                  if (min > W[i][j]) {
                      min = W[i][j];
                      first = i;
                      last = j;
                  }
              }
          }
        }
      }
      printf("%d -> %d, weight = %d \n", first+1, last+1, W[first][last]);
    int nx, ny;
      matrixofTree[first][last] = 1;
      int i=0;
       linesOfGraph(hdc, matrixofTree, nx, ny, first, last);
       vertexOfGraph(hdc, nx, ny, numVerticle, i);
       i++;
      sum+=W[first][last];
      currentVert[last] = true;
      vertNum++;
    }
    printf("Total sum = %d \n", sum);
    for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                printf("%i ", matrixofTree[i][j]);
            }
            printf("\n");
        }

}
    void matrixW(HDC hdc,int matrix[12][12], int* W[12][12]) {
    int B[12][12];
    int C[12][12];
    int D[12][12];
    int Wt[12][12];
    int Tr[12][12]={
            {1,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,0,0,0},
            {1,1,1,1,1,1,1,1,1,0,0,0},
            {1,1,1,1,1,1,1,1,1,1,0,0},
            {1,1,1,1,1,1,1,1,1,1,1,0},
            {1,1,1,1,1,1,1,1,1,1,1,1}
    };

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            Wt[i][j] = roundf((rand() / (float)RAND_MAX * 2) * 100) * matrix[i][j];
            if (Wt[i][j] == 0) B[i][j] = 0;
            else B[i][j] = 1;
        }
    }
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (B[i][j] != B[j][i]) C[i][j] = 1;
            else C[i][j] = 0;

            if (B[i][j] == B[j][i] && B[i][j] == 1 && j <= i) D[i][j] = 1;
            else D[i][j] = 0;
        }
    }
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            Wt[i][j] = (C[i][j] + (D[i][j])) * Wt[i][j];
        }
    }
    symmetricalMatrix(Wt, W); 
}

    switch(messg){
        case WM_PAINT :

            hdc=BeginPaint(hWnd, &ps);

            int n=12;
            char *nn[12] = {"1","2","3","4","5","6","7","8","9","10","11", "12"};
            int nx[12] = {};
            int ny[12] = {};
            int dx = 16, dy = 16, dtx = 5;
            int i, j;
            int radius = 200;
            int centreX = 400;
            int centreY = 200;
            for (int i = 0; i < n; i++){
                nx[i] = centreX + radius * cos(2*pi*i/(n));
                ny[i] = centreY + radius * sin(2*pi*i/(n));
            }

            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
            HPEN RPen = CreatePen(PS_SOLID, 2, RGB(250, 0, 0));


        int W[12][12] = {};
        int symMatrix[12][12] = {};
        double coef=1.0 - 2 * 0.01 - 5 * 0.005 - 0.05;
        int A[12][12];
        int treeMatrix[12][12] = {};
        mulmr(A, coef);
             for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%i ", A[i][j]);
            }
            printf("\n");
        }
        symmetricalMatrix(A, symMatrix);
        printf("\nSymmetrical matrix\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%i ", symMatrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        matrixW(hdc,A,W);
         for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%i ", W[i][j]);
            }
            printf("\n");
        }

SelectObject(hdc, KPen);

   for(int i=0;i < n; i++){
            for(int j=0; j < n; j++) {
            linesOfGraph(hdc, symMatrix, nx,  ny,  i,  j);
            linesWeight(hdc, W, nx,  ny,  i,  j);
            }
            }
        SelectObject(hdc, BPen);

           for(i=0;i < n;i++){
              vertexOfGraph(hdc, nx,  ny,  nn,  i);
            }

         algorythmPrima(W,nx,ny,nn);

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
