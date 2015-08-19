#include <Gamer.h>
#define w 8
#define h 8

Gamer gamer;

int currState[w][h];
int nextState[w][h];
int gx = 2;//glider x position
int gy = 2;//glider x position

void setup(){
  gamer.begin();
  glider(gx,gy);
}
void loop(){
  handleInput();
  gamer.clear();
  //draw live cells
  for(int i=0; i<w; i++)
  {
    for(int j=0; j<h; j++)
    {
      if(currState[i][j] == 1)
      {  
        gamer.display[i][j] = 1;
      }
        //count alive neighbours
        int aliveCells = 0;
        for(int m=-1; m<=1; m++)
        {
          for(int k=-1; k<=1; k++)
          {
            if(!(m==0 && k==0))
            {
              if(currState[(m+i+w)%w][(k+j+h)%h]==1)
              {
                aliveCells++;
              }
            }
          }
        }
        //set next generation
        if(aliveCells < 2 || aliveCells > 3) nextState[i][j] = 0;
        else if(aliveCells==3 )              nextState[i][j] = 1;
        else                                 nextState[i][j] = currState[i][j];
      }
    }
    //set next state
    for(int i=0; i < w; i++)
      for(int j=0; j < h; j++)
        currState[i][j] = nextState[i][j];
  if(gamer.isHeld(UP) || gamer.isHeld(DOWN) || gamer.isHeld(LEFT) || gamer.isHeld(RIGHT)) gamer.display[gx][gy] = 1;
  gamer.updateDisplay();
  delay(40);
}
void glider(int x, int y)
{
  currState[x][y] = 1;
  currState[x-1][y] = 1;
  currState[x+1][y] = 1;
  currState[x+1][y-1] = 1;
  currState[x][y-2] = 1;
}
void handleInput(){
  if(gamer.isPressed(UP) && gy > 0) gy--;
  if(gamer.isPressed(DOWN) && gy < h-1) gy++;
  if(gamer.isPressed(LEFT) && gx > 0) gx--;
  if(gamer.isPressed(RIGHT) && gx < w-1) gx++;
  if(gamer.isPressed(START)) glider(gx,gy);
}
