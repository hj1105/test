#include"declaration.h"

void DF::GotoXY(int x,int y)
{
    COORD C;

    C.X=x;
    C.Y=y;
    SetConsoleCursorPosition(g_HndOut,C);
}

void DF::GotoXY(COORD crd)
{
    SetConsoleCursorPosition(g_HndOut,crd);
}

void DF::HideConsoleCursor()
{
    CONSOLE_CURSOR_INFO cci;

    cci.dwSize=100;
    cci.bVisible=FALSE;
    SetConsoleCursorInfo(g_HndOut,&cci);
}

void DF::SetColor(int text,int _back)
{
    SetConsoleTextAttribute(g_HndOut,text+16*_back);
}

void DF::ClearConsoleScreen()
{
    DWORD dw;

    FillConsoleOutputCharacter(g_HndOut,' ',300*300,{0,0},&dw);
}

inline int rnd2o4()
{
    return ((rand()%2)+1)*2;
}

void RandNumGen(v2d& Map,vector<pair<int,int>>& chk)
{
    pair<int,int> tpir;

    tpir=chk[rand()%chk.size()];
    chk.erase(find(chk.begin(),chk.end(),tpir));
    Map[tpir.first][tpir.second]=rnd2o4();
}

void UpdateScreen(v2d Map)
{
    DF::ClearConsoleScreen();
    DF::GotoXY(0,0);

    for(auto a:Map)
    {
        for(auto b:a) printf("%d ",b);
        puts("");
    }
}

bool IsntGameOver(v2d Map)
{
    return true;
}

void MoveS(v2d& Map,vector<pair<int,int>>& chk)
{
    int i,j,l;
    int tmp;
    for(i=Map.size()-1;i>=0;i--)
    {
        for(j=0;j<Map[i].size();j++)
        {
            if(Map[i][j])
            {
                for(l=i+1;printf("%d %d\n",l,j),l<Map[i].size() && !Map[l][j];l++);
                tmp=Map[i][j];
                if(Map[l][j]==tmp)
                {                   puts("C");
                    chk.push_back(make_pair(i,j));
                    Map[i][j]=0;
                    Map[l][j]*=2;
                    puts("D");
                }
                printf("%d %d\n",l,tmp);
            }
        }
    }
}

void MoveW(v2d& Map,vector<pair<int,int>>& chk)
{
    MessageBoxA(NULL,"W","W",MB_OK);
}

void MoveA(v2d& Map,vector<pair<int,int>>& chk)
{
    MessageBoxA(NULL,"A","A",MB_OK);
}

void MoveD(v2d& Map,vector<pair<int,int>>& chk)
{
    MessageBoxA(NULL,"D","D",MB_OK);
}

int GetDir()
{
    BYTE ch=getch();
    if(isalpha(ch))
    {
        if(islower(ch)) ch-=(int)('a'-'A');
        switch(ch)
        {
            case 'S':
                return 0;
            case 'W':
                return 1;
            case 'A':
                return 2;
            case 'D':
                return 3;
        }
    }
    else if(ch==ARROW_FIRST)
    {
        ch=getch();

        switch(ch)
        {
            case ARROW_DOWN:
                return 0;
            case ARROW_UP:
                return 1;
            case ARROW_LEFT:
                return 2;
            case ARROW_RIGHT:
                return 3;
        }
    }
    return -1;
}

void StartGame()
{
    v2d MapArray(4);
    vector<pair<int,int>> chk;
    void (*fpArr[])(v2d&,vector<pair<int,int>>&)={MoveS,MoveW,MoveA,MoveD};
    int i,j,tmp;

    DF::ClearConsoleScreen();
    srand(time(NULL));
    for(i=0;i<4;i++)
    {
        MapArray[i].resize(4);

        for(j=0;j<4;j++) chk.push_back(make_pair(i,j));
    }
    RandNumGen(MapArray,chk);
    RandNumGen(MapArray,chk);
    UpdateScreen(MapArray);

    while(IsntGameOver(MapArray))
    {
        if((tmp=GetDir())==-1) continue;
        else fpArr[tmp](MapArray,chk);
        UpdateScreen(MapArray);
    }
    return;
}

void PrintStartScreen()
{
    char ch;

    DF::GotoXY(10,5);
    printf("Press \'S\'to start or \'E\'to exit the game.");

    while(true)
    {
        ch=getch();

        if(ch=='S' || ch=='s') StartGame();
        if(ch=='E' || ch=='e')
        {
            DF::ClearConsoleScreen();
            exit(0);
        }
    }
}

void GameMenu()
{
    SetConsoleTitleA("Game Project 2048 | Made by et5_2");
    DF::HideConsoleCursor();
    PrintStartScreen();
}


int main(void)
{
    GameMenu();

    return 0;
}
