#include <fstream>
#include <sstream>
#include <iostream>

int main()
{
   using namespace std;

   ifstream file("input.txt");
   if (!file)
   {
      return 1;
   }

   // current line of input
   string line;

   // vector for storing the reports (on each line)
   vector<vector<int>> reports;

   while (getline(file, line))
   {
      // split the line into tokens (each token is a level)
      vector<std::string> tokens;
      istringstream iss(line);
      copy(istream_iterator<string>(iss),
           istream_iterator<string>(),
           back_inserter(tokens));

      // vector for storing the levels as integers
      vector<int> levels;
      for (string token : tokens)
      {
         levels.push_back(stoi(token));
      }

      // add the levels to the reports
      reports.push_back(levels);
   }

   // Part B - identify the number of safe reports (updated/overwritten part A)
   int safe_reports = 0;

   for (vector<int> levels : reports)
   {
      for (int i = 0; i < levels.size(); i++)
      {
         // Run each report through the "Problem Dampener" because Advent of Code is fun like that. lol
         vector<int> dampened_levels;
         for (int j = 0; j < levels.size(); j++)
         {
            if (j != i)
            {
               dampened_levels.push_back(levels[j]);
            }
         }

         bool is_ascending = false;
         bool is_descending = false;

         bool is_safe = true;

         for (int k = 1; k < dampened_levels.size(); k++)
         {
            int current_level = dampened_levels[k];
            int previous_level = dampened_levels[k - 1];

            // if the current level is the same as the previous level, the report is not safe
            if (current_level == previous_level)
            {
               is_safe = false;
               break;
            }

            // on the first iteration, determine if the report is ascending or descending
            if (k == 1)
            {
               if (current_level > previous_level)
               {
                  is_ascending = true;
                  is_descending = false;
               }
               else if (current_level < previous_level)
               {
                  is_descending = true;
                  is_ascending = false;
               }
            }

            // if the report is ascending or descending, check if the levels are in the correct order
            if (is_ascending && (current_level < previous_level))
            {
               is_safe = false;
               break;
            }
            else if (is_descending && (current_level > previous_level))
            {
               is_safe = false;
               break;
            }
            // if the difference between the current level and the previous level is greater than 3 or less than 1, the report is not safe
            else if (abs(current_level - previous_level) > 3 || abs(current_level - previous_level) < 1)
            {
               is_safe = false;
               break;
            }
         }

         // if any of the dampened versions return true, the report is safe
         if (is_safe)
         {
            safe_reports++;
            break;
         }
      }
   }

   cout << "Number of safe reports: " << safe_reports << endl;

   return 0;
}
