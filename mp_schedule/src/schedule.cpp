/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <queue>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

using namespace std;
/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    V2D output;
    std::string line;
    std::ifstream reader(filename);
    if(!reader.is_open()) {
        return output;
    }
    while(std::getline(reader, line)) {
        std::stringstream ss(line);
        std::vector<std::string> vect;
        while(ss.good()) {
            std::string substr;
            std::getline(ss, substr, ',');
            vect.push_back(Trim(substr));
        }
        output.push_back(vect);
    }
    reader.close();
    return output;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE
    unordered_map<string, set<string>> student_map;
    for(const vector<string>& finder : student) {
        if(finder.empty()) {
            continue;
        }
        set<string> classnames(finder.begin() + 1, finder.end());
        student_map.insert(pair<string, set<string>>(finder.front(), classnames));
    }
    V2D output;
    for(const vector<string>& vect : cv) {
        if(vect.empty()) {
            continue;
        }
        vector<string> _classlist;
        //The name of the "class" in the roster is the front of the vector.
        string classname = vect.front();
        _classlist.push_back(classname);
        for(unsigned i = 1; i < vect.size(); i++) {
            //If the student within the roster is absent, ignore
            if(student_map.count(vect.at(i)) == 0) {
                continue;
            }
            //If the student is not enrolled in that class, ignore
            if(student_map.at(vect.at(i)).count(classname) == 0) {
                continue;
            }
            //Insert the student name to the classlist.
            _classlist.push_back(vect.at(i));
        }
        //If the "class" size is 1, i.e. there are no enrolled students,
        //Ignore it.
        if(_classlist.size() <= 1) {
            continue;
        }
        output.push_back(_classlist);
    }
    return output;
}

unordered_map<string, set<string>> getClassMap(const V2D &courses) {
    unordered_map<string, set<string>> class_students(courses.size() * 10);
    unordered_map<string, set<string>> output(courses.size() * 10);
    for(const vector<string>& studentslist : courses) {
        class_students.insert(pair<string, set<string>>(studentslist.front(), set<string>()));
        output.insert(pair<string, set<string>>(studentslist.front(), set<string>()));
        for(unsigned i = 1; i < studentslist.size(); i++) {
            class_students.at(studentslist.front()).insert(studentslist.at(i));
        }
    }
    for(pair<string, set<string>> course1 : class_students) {
        for(pair<string, set<string>> course2 : class_students) {
            if(course1.first == course2.first) {
                continue;
            }
            for(string student : course1.second) {
                if(course2.second.count(student) != 0) {
                    output.at(course1.first).insert(course2.first);
                    break;
                }
            }
        }
    }
    return output;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    //V2D mocker = courses;
    //mocker.push_back(timeslots);
    //return mocker;
    //an unsigned will be used for color.
    
    //unordered_map<string, set<string>> classnames;
    unordered_map<string, set<string>> classnames = getClassMap(courses);
    //classnames is constructed later
    //does this over and over until it succeeds and returns, or until it runs out of start points.
    for(pair<string, set<string>> current_node : classnames) {
        //coloring map with 10 times the number of courses (large for efficiency)
        //The key is the course name. The value is the timeslot index aka color
        unordered_map<string, unsigned> colormap(courses.size() * 10);
        //holds classnames for traversal
        queue<string> traversal;
        traversal.push(current_node.first);
        while(!traversal.empty()) {
            string coursename = traversal.front();
            //valid colors are unsigned values.
            //This vector has indices of boolean to indicate weather or not a color can be used.
            vector<bool> valid_colors(timeslots.size(), false);
            for(string adjacent : classnames.at(coursename)) {
                if(colormap.count(adjacent) == 0) {
                    traversal.push(adjacent);
                } else {
                    valid_colors.at(colormap.at(adjacent)) = true;
                }
            }
            //Find the first valid color (false in valid_colors vector)
            unsigned color_val = 0;
            while(color_val < valid_colors.size() && valid_colors.at(color_val)) {
                color_val++;
            }
            //if there are no valid colors, break.
            if(color_val == valid_colors.size()) {
                break;
            }
            colormap.insert(pair<string, unsigned>(coursename, color_val));
            traversal.pop();
        }
        //traversal is empty after a successful assigning.
        //stop and return successful result.
        if(traversal.empty()) {
            V2D output;
            for(const string& timeslot : timeslots) {
                output.push_back(vector<string>(1, timeslot));
            }
            for(pair<string, unsigned> colored_course : colormap) {
                output.at(colored_course.second).push_back(colored_course.first);
            }
            return output;
        }
    }
    return V2D(1, vector<string>(1, "-1"));
}