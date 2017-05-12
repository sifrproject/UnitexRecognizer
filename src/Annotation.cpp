#include "Annotation.h"

/**
 * \file Annotation.cpp
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

Annotation::Annotation(std::string termID, std::string term, int from, int to) {
    this->termID = termID;
    this->term = term;
    this->term.erase(std::find_if(this->term.rbegin(), this->term.rend(),
                        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), this->term.end()); // used to clean up term
    this->from = from;
    this->to = to;
}

std::string Annotation::getTermID() {
    return this->termID;
}

std::string Annotation::getTerm() {
    return this->term;
}

int Annotation::getFrom() {
    return this->from;
}

int Annotation::getTo() {
    return this->to;
}

