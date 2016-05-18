#include <Rcpp.h>
#include <vector>

using namespace Rcpp;


String join2(const CharacterVector &tokens, 
             const String &delim){
  if(tokens.size() == 0) return "";
  String token = tokens[0];
  int len_ngram = tokens.size();
  for (int i = 1; i < len_ngram; i++) {
    token += delim;
    token += tokens[i];
    //Rcout << "Joined " << token.get_cstring()  << "\n";
  }
  token.set_encoding(CE_UTF8);
  return token;
}

// [[Rcpp::export]]
CharacterVector join_tokens_cpp(CharacterVector tokens_original, 
                                CharacterVector tokens_join,
                                const String &delim){
  //CharacterVector tokens(x);
  CharacterVector tokens = clone(tokens_original);
  int len = tokens.size();
  int len_join = tokens_join.size();
  if(len_join == 1){ // Do nothing for single token
    return tokens ;
  }
  int start = -1;
  bool change = FALSE;
  String token_joined = join2(tokens_join, delim);
  for (int i = 0; i < len - (len_join - 1); i++){
    //Rcout << "Now " << i << " " << tokens[i] << "\n";
    if(tokens[i] == tokens_join[0] & tokens[i + 1] == tokens_join[1]){ // Initial match
      start = i;
      //Rcout << "Start " << start << " " << tokens[i] << "\n";
    }
    if(start > -1){
      int j = i - start;
      if(j == len_join - 1){ // Complete match
        //Rcout << "End " << start << " " << tokens[i] << "\n";
        tokens[start] = token_joined;
        for(int k = start + 1; k < start + len_join; k++){
          //Rcout << "Remove " << k << ' ' << tokens[k] << "\n";
          tokens[k] = "";
        }
        change = TRUE;
        start = -1; // Reset
      }else{
        if(tokens[i] != tokens_join[j]) start = -1; // Partial match
      }
    }
  }
  
  CharacterVector tokens_joined(len);
  int space = 0;
  if(change){
    //Rcout << "Remove spacer\n";
    int j = 0;
    for (int i = 0; i < len; i++){
      if(tokens[i] != ""){
        tokens_joined[j] = tokens[i];
        j++;
      }
      
    }
    //Rcout << "Done\n";
    return tokens_joined[seq(0, j - 1)];
  }else{
    return tokens_original; // Return original if there is no change
  }
  
}

// [[Rcpp::export]]
List join_tokens_cppl(List texts_original, 
                      const std::vector<bool> &flag,
                      const CharacterVector &tokens_join,
                      const String &delim){
  //List texts(x);
  List texts = clone(texts_original);
  int len = texts.size();
  if(flag.size() != len){
    Rcout << "Invalid flag is given\n";
    return texts;
  }
  for (int h = 0; h < len; h++){
    if(flag[h]){
      //Rcout << "Text " << h << "\n";
      texts[h] = join_tokens_cpp(texts[h], tokens_join, delim);
    }
  }
  return texts;
}

