#include <bits/stdc++.h>
#include <windows.h>
#include <cstdlib>

using namespace std;

void return_randomstate(int height, int width, int* arr)
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            float random = (float) rand()/RAND_MAX;
            if(random>0.50)
                *(arr+i*width+j) = 1;
            else
                *(arr+i*width+j) = 0;
        }
    }
}

void print(int height, int width, int* arr)
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            cout << *(arr+i*width+j) << " ";
        }
        cout << endl;
    }
}

void render(int height, int width, int* arr)
{
    for(int i=-1; i<height+1; i++)
    {
        for(int j=-1; j<width+1; j++)
        {
            if(i==-1 || i==height)
                cout << "-";
            else if(j==-1 || j==width)
                cout << "|";
            else
            {
                if(*(arr+i*width+j)==1)
                    cout << "*";
                else
                    cout << ".";
            }
        }
        cout << endl;
    }
}

int count_live_neighbour_cell(int r, int c, int* arr, int height, int width)
{
    int i, j, count = 0;
    for (i = r - 1; i <= r + 1; i++)
    {
        for (j = c - 1; j <= c + 1; j++)
        {
            if ((i == r && j == c) || (i < 0 || j < 0) || (i >= height || j >= width))
            {
                continue;
            }
            if (*(arr+i*width+j) == 1)
            {
                count++;
            }
        }
    }
    return count;
}

void calculate_next_state(int height, int width, int* arr1, int* arr)
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            int live_neighbours = count_live_neighbour_cell(i,j,(int *)arr1,height,width);
            if (*(arr1+i*width+j) == 1 && (live_neighbours == 2 || live_neighbours == 3))
            {
                *(arr+i*width+j) = 1;
            }

            else if (*(arr1+i*width+j) == 0 && live_neighbours == 3)
            {
                *(arr+i*width+j) = 1;
            }

            else
            {
                *(arr+i*width+j) = 0;
            }
        }
    }
}

void equality(int height, int width,int* arr, int* arr1)
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            *(arr1+i*width+j) = *(arr+i*width+j);
        }
    }
}

int main()
{
    srand(time(0)+clock());
    int height,width;
    cout << "Enter height of board : ";
    cin >> height;
    cout << "Enter width of board : ";
    cin >> width;
    system("CLS");
    int randomstate[height][width];
    int nextstate[height][width];
    int previousstate[height][width];
    return_randomstate(height,width,(int*)randomstate);
    equality(height, width,(int *)randomstate,(int *)previousstate);
    for(int i = 0; i < 1000; i++)
    {
        calculate_next_state(height,width,(int *)previousstate,(int *)nextstate);
        system("CLS");
        render(height,width,(int *)previousstate);
        Sleep(1000);
        equality(height,width,(int *)nextstate, (int *)previousstate);
    }
    return 0;
}
