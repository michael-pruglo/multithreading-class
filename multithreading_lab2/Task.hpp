//
// Created by Michael on 10/15/17.
//

#ifndef MULTITHREADING_LAB2_TASK_HPP
#define MULTITHREADING_LAB2_TASK_HPP


class Task
{
    int type;
    int id;

public:
    Task(int type, int id) : type(type), id(id) {}

    int getType() const {return type;}
    int getId() const {return id;}
};


#endif //MULTITHREADING_LAB2_TASK_HPP
