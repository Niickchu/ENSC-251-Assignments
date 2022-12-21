
//stu_sort.cpp to implement your sorting functions
#include "stu_sort.hpp"
#include <string>

void Sort_All(vector<DomesticStudent> &in_vec) // a function that uses bubble sort with other nested if statements in order to
	{										   // appropriately sort the vector of domestic students 
        int n = in_vec.size();
        int i, j;
        for (i = 0; i < n - 1; i++)
        {
                for (j = 0; j < n - i - 1; j++)
                {
                        int res_compare = compareResearchScore(in_vec[j], in_vec[j + 1]);
                        if (res_compare == -1 || res_compare == 0)
                        {
                                if (res_compare == -1) // checks if the the research scores are the same and if they are 
                                {					   // continue to the next condition. Otherwise, swap the elements
                                        swap_stu<DomesticStudent>(&in_vec[j], &in_vec[j + 1]);
                                }
                                else
                                {
                                        int cgpa_compare = compareCGPA(in_vec[j], in_vec[j + 1]);

                                        if (cgpa_compare == -1) // checks if the cgpas are the same and if they are 
                                        {						// continue to the next condition. Otherwise, swap the elements
                                                swap_stu<DomesticStudent>(&in_vec[j], &in_vec[j + 1]);
                                        }
                                        else
                                        {
                                                int province_compare = compareProvince(in_vec[j], in_vec[j + 1]);
                                                if (province_compare == -1) // checks to see which province comes before and swap the elemtes accordingly
                                                        swap_stu<DomesticStudent>(&in_vec[j], &in_vec[j + 1]);
                                                }
                                        }
                                }
                        }
                }
        }


/*
	A function using bubble sort to sort through a vector of 
	iternational students and then return a new sorted vector
*/
vector<InternationalStudent> Sort_All(vector<InternationalStudent> in_vec)
{
		vector<InternationalStudent> return_vec;
        int n = in_vec.size();
        int i, j;
        for (i = 0; i < n - 1; i++)	// uses bubble sort to go through the vector
        {
                for (j = 0; j < n - i - 1; j++)
                {
                        if (in_vec.size() >= j + 1)
                        {
							// checks if the the research scores are the same and if they are 
							// continue to the next condition. Otherwise, swap the elements
                            int res_compare = compareResearchScore(in_vec[j], in_vec[j + 1]); 
                            if (res_compare == -1 || res_compare == 0)
                            {
                                if (res_compare == -1)
                                {
                                    swap_stu<InternationalStudent>(&in_vec[j], &in_vec[j + 1]);
                                }
                                else
                                {
                                    int cgpa_compare = compareCGPA(in_vec[j], in_vec[j + 1]);
									// checks if the cgpas are the same and if they are 
									// continue to the next condition. Otherwise, swap the elements
                                    if (cgpa_compare == -1)
                                    {
                                        swap_stu<InternationalStudent>(&in_vec[j], &in_vec[j + 1]);
                                    }
                                    else
                                    {
                                        int province_compare = compareCountry(in_vec[j], in_vec[j + 1]);
                                        if (province_compare < 0)	// checks to see which country comes before and swap the elemtes accordingly
                                        {
                                            swap_stu<InternationalStudent>(&in_vec[j], &in_vec[j + 1]);
                                        }
                                    }
                                }
                            }
                        }
                }
        }

		for(auto i: in_vec){	// only adds the elements that have a valid toefl score to the returning vector
			
			if(i.valid_toefl()){
				return_vec.push_back(i);
			}

		}

        return return_vec;
}