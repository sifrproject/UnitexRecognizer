#ifndef RECOGNIZER_ANNOTATION_H
#define RECOGNIZER_ANNOTATION_H

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * \file Annotation.h
 * \brief A semantic annotation of the text.
 * \author Stella Zevio
 * \date May 2017
 *
 * A semantic annotation consists in recognizing a concept of an ontology in the text.
 * Ontologies' concepts are stored in a dictionary that Unitex handles.
 * When an ontology concept is recognized in the text, an annotation is created.
 * An annotation is composed of :
 * the annotation itself (ID of the recognized ontology concept),
 * the annotated token in the text (section of text where the ontology concept has been recognized),
 * the starting and ending positions of the annotated token in the text.
 */

class Annotation {

private:
    std::string termID; /**< annotation (redis ID of the recognized ontology concept) */
    std::string term; /**< annotated token in the text */
    int from; /**< starting position of annotated token in the text (absolute) */
    int to; /**< ending position of annotated token in the text (absolute) */

public:
    /**
     * \brief Annotation constructor
     * \param termID - redis ID of the recognized ontology concept (annotation)
     * \param term - annotated token in the text
     * \param from - starting position of annotated token in the text (absolute)
     * \param to - ending position of annotated token in the text (absolute)
     */
    Annotation(std::string termID, std::string term, int from, int to);

    /**
     * \brief Get ID of the recognized ontology concept
     * \return termID
     */
    std::string getTermID();

    /**
     * \brief Get annotated token in the text
     * \return term
     */
    std::string getTerm();

    /**
     * \brief Get starting position of the annotated token in the text
     * \return from
     */
    int getFrom();

    /**
     * \brief Get ending position of the annotated token in the text
     * \return to
     */
    int getTo();
};


#endif
