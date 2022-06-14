//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Pavel Marek <xmarek75@stud.fit.vutbr.cz>
// $Date:       $2021-03-12
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Pavel Marek
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()
{
    Element_t *element = GetHead();
    while(element != NULL)
    {
        Element_t *tmp = element;
        element = element->pNext;
        delete tmp;
    }

}

void PriorityQueue::Insert(int value)
{
    if(m_pHead == NULL)
    {
        m_pHead = new Element_t{
            .pNext = nullptr,
            .value = value
        };
        return;
    }

    //going through whole line
    for (Element_t *element = GetHead(); element != NULL; element = element->pNext)
    {
        // insert to the first place
        if(element == m_pHead && element->value <= value)
        {
            m_pHead = new Element_t{
                .pNext = element,
                .value = value
            };
            return;
        }
        // insert to somewhere in the middle
        else if(element->pNext != NULL && element->pNext->value <= value && element->value > value)
        {
            Element_t *inserted = new Element_t{
                .pNext = element->pNext,
                .value = value
            };
            element->pNext = inserted;
            return;
        }
        //insert to the last place
        else if(element->pNext == NULL && element->value > value)
        {
            Element_t *inserted = new Element_t{
                    .pNext = nullptr,
                    .value = value
            };
            element->pNext = inserted;
            return;
        }

    }

return;
}

bool PriorityQueue::Remove(int value)
{
    if (Element_t *found = Find(value))
    {
        //if element is in first place
        if(found == m_pHead)
        {
            m_pHead = m_pHead->pNext;
            return true;
        }
        //if element is in the last place
        if(found->pNext == NULL)
        {
            for(Element_t *element = GetHead(); element != NULL; element = element->pNext)
            {
                if(element->pNext->value == found->value)
                {
                    element->pNext = nullptr;
                }
            }
            return true;
        }
        //if element is somewhere in the middle
        if(found->pNext != NULL)
        {
            for(Element_t *element = GetHead(); element != NULL; element = element->pNext)
            {
                if(element->pNext == found)
                {
                    element->pNext = found->pNext;
                }
            }
            return true;
        }

    }
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    for(Element_t *element = GetHead(); element != NULL; element = element->pNext)
    {
        if(element->value == value)
        {
            return element;
        }
    }
    return NULL;
}

size_t PriorityQueue::Length()
{
    int i = 0;
    for (Element_t *element = GetHead(); element != NULL; element = element->pNext)
    {
            i += 1;
    }

	return i;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
