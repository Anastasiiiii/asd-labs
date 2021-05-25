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
        980,
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

        for(int i = 0; i < 12; i++) {
            if(i == 0) {
                nx[i] = 100;
                ny[i] = 450;
            } else if(i < 5) {
                nx[i] = nx[i - 1] + 100;
                ny[i] = ny[i - 1] - 100;
            } else if(i < 9) {
                nx[i] = nx[i - 1] + 100;
                ny[i] = ny[i - 1] + 100;
            } else {
                nx[i] = nx[i - 1] - 200;
                ny[i] = ny[i - 1];
            }
        }


        srand(0425);
        double** T = randm(12, 12);
        double** mulmr(double coef, double** matrix, int rows, int cols);
        double coef = 1 - 2*0.02 - 5*0.005 - 0.25;
        double** A = mulmr(coef, T, 12, 12);
            for (int i = 0; i < 12; i++) {
                for (int j = 0; j < 12; j++) {
                    printf("%g ", A[i][j]);
                }
                printf("\n");
                }
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
                              nxs = (nx[i]+nx[j])/2.6 - (ny[i]-ny[j])/6;
                              nys = (ny[i]+ny[j])/2.6 - (nx[i]-nx[j])/6;
                              MoveToEx (hdc, nx[j], ny[j], NULL);
                              LineTo (hdc, nxs, nys);
                              MoveToEx (hdc, nxs, nys, NULL);
                              LineTo (hdc, nx[i], ny[i]);
                              R = (pow(nx[i] - nx0, 2) + pow(ny[i] - ny0, 2))/sqrt(3);
                              k = atan2(ny[j] - ny[i], nx[j] - nx[i]);
                              m = atan2(sqrt(pow(nx[j] - nx[i], 2) + pow(ny[j] - ny[i], 2)), R/2);
                              arrow((360 - (340/pi*(m + k))), nx[j], ny[j]);
                              continue;
                            }
                            if ((i <= 4) && (j <= 4))
                            {
                              nxs = (nx[i]+nx[j])/2.6 - (ny[i]-ny[j])/6;
                              nys = (ny[i]+ny[j])/2.6 - (nx[i]-nx[j])/6;
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
                              nxs = (nx[i]+nx[j])/1.7 - (ny[i]-ny[j])/6;
                              nys = (ny[i]+ny[j])/1.7 - (nx[i]-nx[j])/6;
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
                            if (((i >= 8) || (i == 0)) && ((j >= 8) || (j == 0)))
                            {
                              nxs = (nx[i]+nx[j])/1.8 - (ny[i]-ny[j])/8;
                              nys = (ny[i]+ny[j])/1.8 - (nx[i]-nx[j])/8;
                              MoveToEx (hdc, nx[j], ny[j], NULL);
                              LineTo (hdc, nxs, nys);
                              MoveToEx (hdc, nxs, nys, NULL);
                              LineTo (hdc, nx[i], ny[i]);
                              R = (pow(nx[i] - nx0, 2) + pow(ny[i] - ny0, 2))/sqrt(3);
                              k = atan2(ny[j] - ny[i], nx[j] - nx[i]);
                              m = atan2(sqrt(pow(nx[j] - nx[i], 2) + pow(ny[j] - ny[i], 2)), R/2);
                              arrow((180 - (340/pi*(m + k))), nx[j], ny[j]);
                              continue;
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
