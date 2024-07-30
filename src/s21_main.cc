#include <cmath>
#include <functional>
#include <iostream>

#include "s21_model.h"

// int main() {
//   s21::Model smt;
//   std::string str = "1-2";
//   std::string str2 = "3+4";

//   //   std::function<double(double, double)> func = std::pow<double, double>;
//   // s21::Token tok;
//   // std::map<std::string, s21::Token> token_map;
//   // smt.CreateTokenMap(token_map);
//   // for (const auto& pair : token_map) {
//   //   std::cout << pair.first << ": " << pair.second.GetAssociativity()
//   //             << std::endl;
//   // }
//   try {
//     smt.CalculateAnswer(str, 0);
//     std::cout << "answer is " << smt.GetAnswer() << std::endl;
//     smt.CalculateAnswer(str2, 0);
//     std::cout << "answer is " << smt.GetAnswer() << std::endl;

//     // smt.printStack();
//     // while (!smt.validated_input_.empty()) {
//     //   s21::Token token = smt.validated_input_.front();
//     //   smt.validated_input_.pop_front();
//     //   std::cout << "Name: " << token.GetName() << std::endl;
//     // std::cout << "Priority: " << token.GetPriority() << std::endl;
//     // std::cout << "Associativity: " << token.GetAssociativity() <<
//     // std::endl; std::cout << "Type: " << token.GetType() << std::endl;
//     // std::cout << "Function result: " << token.GetValue() << std::endl;
//     // }
//   } catch (const std::exception& e) {
//     std::cerr << "Error: " << e.what() << std::endl;
//   }
//   return 0;
// }
