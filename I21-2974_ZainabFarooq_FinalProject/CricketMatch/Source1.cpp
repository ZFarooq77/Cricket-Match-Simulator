//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//using namespace std;
//
//int main()
//{
//    string testline;
//    string word[6][3];
//
//    ifstream Test ( "Data.txt" );
//
//    if (!Test)
//    {
//        cout << "There was an error opening the file.\n";
//        return 0;
//    }
//    //store words in array
//    int x=0,y=0;
//    while( Test>>testline )
//    {
//        word[y][x]=testline;
//        x++;
//        if (testline=="")
//        y++;
//    }
//    //output whole array with array position numbers for each entry
//    cout<<"Array contents:\n";
//        for (int y=0;y<6;y++)
//        {
//            for (int x=0;x<3;x++)
//            cout<<word[y][x]<<"("<<y<<","<<x<<")"<<endl;
//        }
//
//    return 0;
//}