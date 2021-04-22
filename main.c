#include<windows.h>
#include<math.h>
#define pi 3.14159265358979323846

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

char ProgName[]="lab 3";

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
        400,
        100,
        840,
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

    void arrow(float fi, int px,int py){
            px=px-16*cos(fi);
            py=py-16*sin(fi);
            int lx,ly,rx,ry;
            lx = px-15*cos(fi+0.3);
            rx = px-15*cos(fi-0.3);
            ly = py-15*sin(fi+0.3);
            ry = py-15*sin(fi-0.3);
            MoveToEx(hdc, lx, ly, NULL);
            LineTo(hdc, px, py);
            LineTo(hdc, rx, ry);
      }

    switch(messg){
        case WM_PAINT :
            hdc=BeginPaint(hWnd, &ps);
            char *nn[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
            int nx[12] = {};
            int ny[12] = {};
            int num = 100;
            int len = 600;
        for(int i = 0; i < 12; i++) {
            if(i == 0) {
                nx[i] = num;
                ny[i] = num + sqrt(3)*len/2;
            } else if(i < 5) {
                nx[i] = nx[i - 1] + len/4*cos(pi/3);
                ny[i] = ny[i - 1] - len/4*sin(pi/3);
            } else if(i < 9) {
                nx[i] = nx[i - 1] + len/4*cos(pi/3);
                ny[i] = ny[i - 1] + len/4*sin(pi/3);
            } else {
                nx[i] = nx[i - 1] - len/4;
                ny[i] = ny[i - 1];
            }
        }
        int i, dx = 16, dy = 16, dtx = 5;
        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

        srand(0425);
        double** T = randm(12, 12);
        double coefficient = 1 - 2*0.02 - 5*0.005 - 0.25;
        double** A = mulmr(coefficient, T, 12, 12);
            for (int i = 0; i < 12; i++) {
                for (int j = 0; j < 12; j++) {
                    printf("%g ", A[i][j]);
                }
                printf("\n");
        }
int scaler = 1.1;
int nx0, ny0, R;
SelectObject(hdc, KPen);

            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){
                    if (A[i][j] == 1){
                            if (i == j){
                                Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]-40, nx[j], ny[j], nx[j], ny[j]);
                                arrow(2, nx[j], ny[j]);
                                continue;
                            }
                            if  ((A[j][i]==1) && (i>j))
                            {
                                nx0=(nx[i]+nx[j])/2 - (ny[i]-ny[j]);
                                ny0=(ny[i]+ny[j])/2 + (nx[i]-nx[j]);
                                R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                                Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[i], ny[i], nx[j], ny[j]);
                                arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])-atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
                                continue;
                            }
                            if (((i==0) && (j==10))||((i==10) && (j==0))||(i==j+1)||(i==j-1))
                             {
                                MoveToEx(hdc, nx[i], ny[i], NULL);
                                LineTo(hdc, nx[j], ny[j]);
                                arrow(atan2(ny[j]-ny[i],nx[j]-nx[i]),nx[j],ny[j]);
                                continue;
                            }

                            if ((i < 5) && ((j < 5)))
                                {
                                nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
                                ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
                                R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                                Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
                                arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])+atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
                                continue;
                               }
                            if ((i>=4) &&(i < 9)&& (j>=4) &&(j < 9))
                            {
                                nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
                                ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
                                R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                                Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
                                arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])+atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
                                continue;
                            }
                            if (((i>=8) || (i==0)) && ((j>=8)||(j==0)))
                            {
                                nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
                                ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
                                R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                                Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
                                arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])+atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
                                continue;
                            }
                        MoveToEx(hdc, nx[i], ny[i], NULL);
                        LineTo(hdc, nx[j], ny[j]);
                        arrow(atan2(ny[j]-ny[i],nx[j]-nx[i]),nx[j],ny[j]);
                    }
                }
            }
            SelectObject(hdc, BPen);
            for(i=0;i < 12;i++){
              Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
              TextOut(hdc, nx[i]-dtx,ny[i]-dy/2,  nn[i], 2);
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
