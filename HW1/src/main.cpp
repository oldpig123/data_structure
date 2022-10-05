#include <fstream>
#include <iostream>
using namespace std;

typedef struct {
    char student_name[80];
    char id[11];  //personal id
    char student_id[10];
    char depart[3];  //department
    short mid1;
    short mid2;
    short term;
    short final_s;  //final score
    short age;
} student;

//i write this func. because you want
//it doesn't mean i will use this func. in the program
void sort(student *a, const int n)
// sort the n student a[0] to a[n-1] into non-decreasing order
{
    for (int i = 0; i < n; i++) {
        // find the smallest  from a[i] to a[n-1];
        int s = i;  // s: the smallest index
        for (int k = i + 1; k < n; k++) {
            if (a[k].final_s < a[s].final_s) s = k;
        }
        // interchange
        student temp = a[i];
        a[i] = a[s];
        a[s] = temp;
    }
}
void quick_sort(student *s, int left, int right) {  //quick sort algorithm

    if (left > right) {  //terminate condition
        return;
    }

    int i = left, j = right, temp = s[left].final_s;  //chose a standard val
    student t2 = s[left];

    while (i != j) {  //group data with the smaller at left ane bigger at right

        while (s[j].final_s >= temp && i < j)
            j--;
        while (s[i].final_s <= temp && i < j)
            i++;

        student t = s[i];
        s[i] = s[j];
        s[j] = t;
    }

    s[left] = s[i];  //put the std data at middle
    s[i] = t2;
    quick_sort(s, left, i - 1);   //do it again with smaller side
    quick_sort(s, i + 1, right);  //do it again with bigger side
}

int main(int argc, char *argv[]) {
    fstream in_file("list2.txt");
    int n;
    in_file >> n;
    student s[n];
    cout << "Student Record List Sorted Ascendingly according to Final Score" << endl;
    cout << "Index"
         << "\t"
         << "F_NAME"
         << "\t"
         << "StudentID"
         << "\t"
         << "AGE"
         << "\t"
         << "Mid1"
         << "\t"
         << "Mid2"
         << "\t"
         << "Term"
         << "\t"
         << "Final" << endl;
    for (int i = 0; i < n; i++) {
        //input data from file
        in_file >> s[i].student_name >> s[i].id >> s[i].student_id >> s[i].age >> s[i].depart >> s[i].mid1 >> s[i].mid2 >> s[i].term;
        //cal. final score
        s[i].final_s = (s[i].mid1 + s[i].mid2 + s[i].term) / 3;
    }
    quick_sort(s, 0, n - 1);
    //sort(s, n);
    for (int i = 0; i < n; i++)  //data output
        cout << i << "\t"
             << s[i].student_name << '\t'
             << s[i].student_id << "\t"
             << s[i].age << "\t"
             << s[i].mid1 << "\t"
             << s[i].mid2 << "\t"
             << s[i].term << "\t"
             << s[i].final_s << endl;
    cout << "The student with the highest score: " << endl;
    cout << "F_NAME\t"
         << "\t"
         << ":" << s[n - 1].student_name << endl
         << "ID\t"
         << "\t"
         << ":" << s[n - 1].id << endl
         << "StudentID\t"
         << ":" << s[n - 1].student_id << endl
         << "AGE\t"
         << "\t"
         << ":" << s[n - 1].age << endl
         << "Scores\t"
         << "\t"
         << ":" << s[n - 1].mid1 << "," << s[n - 1].mid2 << "," << s[n - 1].term << endl
         << "Final\t"
         << "\t"
         << ":" << s[n - 1].final_s << endl;
    cout << endl
         << "size of structure \"studednt\" is " << sizeof(student) << " bytes" << endl;
    system("pause");
	in_file.close();
}
