#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "Searchable.h"

#include <memory>
using std::unique_ptr;

#include <queue>
#include <vector>
using std:: priority_queue;
using std:: vector;

struct comp
{
    bool operator()(const unique_ptr<Searchable> & a, const unique_ptr<Searchable> &b)
    {
        return (a->heuristicValue()>b->heuristicValue());
    }
};

class BestFirstSearch {
    protected:
        priority_queue<unique_ptr<Searchable> ,vector<unique_ptr<Searchable>>, comp> Q;
        int nodes = 0;
    public:
        BestFirstSearch(std::unique_ptr<Searchable> && startFrom)
        {
            Q.push(std::move(startFrom));
        }
    
        int getNodesExpanded() const
        {
            return nodes;
        }
    
        Searchable * solve()
        {

            while (!Q.empty())
            {
                if (Q.top()->isSolution())
                {
                    return Q.top().get(); // return the pointer
                }

                ++nodes;

                unique_ptr<Searchable> current(std::move(const_cast<std::unique_ptr<Searchable> &>(Q.top())));

                Q.pop();

                // Get the successors...
                vector<unique_ptr<Searchable>> successors = current->successors();

                for (auto & successor : successors)
                {
                    Q.push(std::move(successor));
                }
            }
            return nullptr;
        }
};

// Do not edit below this line
#endif
