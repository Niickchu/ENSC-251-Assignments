//header file stu_sort.hpp to declare your sorting functions

#include "student.hpp"
#ifndef stu_sort_hpp
#define stu_sort_hpp

#include <vector>
#include <string> //you will have to use string in C++



// Since templates have to be made in the header file they are implemented here
// instead of the cpp file.

// a template function made to swap two student elementes
template <class class_type>
void swap_stu(class_type *stu1, class_type *stu2){

        class_type temp = *stu1;
        *stu1 = *stu2;
        *stu2 = temp;

}

// a template function that uses bubble sort and the compareCGPA function
// to sort the students in a vector by their CGPA
template <class class_type>
void sort_cgpa(vector<class_type> &in_vec){
        int n = in_vec.size();
        int i, j;
        for (i = 0; i < n-1; i++){ 
        for (j = 0; j < n-i-1; j++){
                if(compareCGPA(in_vec[j], in_vec[j+1]) == -1){
                        swap_stu<class_type>(&in_vec[j], &in_vec[j+1]); 
                }
        }
        }
}

// a template function that uses bubble sort and the compareResearchScore function
// to sort the students in a vector by their research score
template <class class_type>
void sort_score(vector<class_type> &in_vec){
        int n = in_vec.size();
        int i, j;
        for (i = 0; i < n-1; i++){ 
        for (j = 0; j < n-i-1; j++){
                if(compareResearchScore(in_vec[j], in_vec[j+1]) == -1){
                        swap_stu<class_type>(&in_vec[j], &in_vec[j+1]); 
                }
        }
        }
}

// a template function that uses bubble sort and the compareFirstName function
// to sort the students in a vector by their first name
template <class class_type>
void sort_firstname(vector<class_type> &in_vec){
        int n = in_vec.size();
        int i, j;
        for (i = 0; i < n-1; i++){ 
        for (j = 0; j < n-i-1; j++){
                if(compareFirstName(in_vec[j], in_vec[j+1]) > 0){
                        swap_stu<class_type>(&in_vec[j], &in_vec[j+1]); 
                }
        }
        }
}

// a template function that uses bubble sort and the compareLastName function
// to sort the students in a vector by their last name
template <class class_type>
void sort_lastname(vector<class_type> &in_vec){
    int n = in_vec.size();
    int i, j;
    for (i = 0; i < n-1; i++){ 
        for (j = 0; j < n-i-1; j++){
                if(compareLastName(in_vec[j], in_vec[j+1]) > 0){
                        swap_stu<class_type>(&in_vec[j], &in_vec[j+1]); 
                }
        }
        }
}

void Sort_All(vector<DomesticStudent> &in_vec);

vector<InternationalStudent> Sort_All(vector<InternationalStudent> orig_vec);


#endif
