#include <Rcpp.h>
using namespace Rcpp;

#define a 0
#define b 1
#define c 2
#define d 3

typedef std::vector< int > vecint;

template<typename Ti, typename Tm>
void contingency_matrix(std::vector<Ti> & table, const Tm & M1, const Tm & M2) {
  
  // Catching error
  if ((M1.ncol() != M2.ncol()) | (M1.nrow() != M2.nrow())) 
    stop("`a` and `b` must have the same dimensions.");
  
  if (table.size() != 4)
    stop("`table` must be of size 4.");
  
  double ans;
  std::fill(table.begin(), table.end(), 0);
  
  int n = M1.nrow();
  int m = M1.ncol();
  
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (i == j) continue;
      else {
        if ((M1(i,j) == M2(i,j)) & (M1(i,j) == 1)) table[a]++;
        else if ((M1(i,j) != M2(i,j)) & (M1(i,j) == 1)) table[b]++;
        else if ((M1(i,j) != M2(i,j)) & (M1(i,j) == 0)) table[c]++;
        else if ((M1(i,j) == M2(i,j)) & (M1(i,j) == 0)) table[d]++;
      }
  
}


template<typename Ti, typename Tm> inline
std::vector<Ti> contingency_matrix(const Tm & M1, const Tm & M2) {
  
  std::vector<Ti> table(4);
  contingency_matrix< Ti, Tm >(table, M1, M2);
  
  return table;
  
}

//' @name similarity
//' @rdname similarity
//' @section Similarity:
//' - Jaccard (1): `"sjaccard"` or `"jaccard"`
//' @aliases Jaccard
double sjaccard(
    const IntegerMatrix & M1,
    const IntegerMatrix & M2,
    bool normalize = false
) {
  
  std::vector<double> table = contingency_matrix<double, IntegerMatrix>(M1, M2);
  
  return table[a]/(table[a] + table[b] + table[c]);
  
}

//' @name similarity
//' @rdname similarity
//' @section Similarity:
//' - Tarwid (54): `"starwid"` or `"tarwid"`.
//' @aliases Tarwid
double starwid(
    const IntegerMatrix & R1,
    const IntegerMatrix & R2,
    bool normalized = false
  ) {
  
  std::vector<double> table = contingency_matrix<double, IntegerMatrix>(R1, R2);
  int n = R1.nrow();
  return (n*table[a] - (table[a] + table[b])*(table[a] + table[c]))/
          (n*table[a] + (table[a] + table[b])*(table[a] + table[c]));
  
}

//' @name similarity
//' @rdname similarity
//' @section Similarity:
//' -  Pearson & Heron 1 (54): `"sph1"` or `"ph1"` or `"s14"`. This is also known as S14 in
//'    Gower and Legendre (1986).
//'    
//'    In the case of the `S14` function, following Krackhardt's 1989:
//'    
//'    \deqn{%
//'    \sqrt{\left(\frac{a}{(a + c)} - \frac{b}{(b + d)}\right)\times\left(\frac{a}{(a + b)} - \frac{c}{(c + d)}\right)}
//'    }{%
//'    S14 = [(a/(a + c) - b/(b + d))*(a/(a + b) - c/(c + d))]^(1/2)
//'    }
//'   
//'    Which is an statistic lying between 0 and 1.
//'  
//' @aliases Person-&-Heron
//' @aliases S14
double sph1(
    const IntegerMatrix & R1,
    const IntegerMatrix & R2,
    bool normalized = false
  ) {
  
  std::vector<double> table = contingency_matrix<double, IntegerMatrix>(R1, R2);
  
  return (table[a]*table[d] - table[b]*table[c])/
    sqrt((table[a] + table[b])*(table[a] + table[c])*(table[b] + table[d])*(table[c] + table[d]));
        
}

//' @name similarity
//' @rdname similarity
//' @section Distance:
//' - Hamming (15): `"dhamming"` or `"hamming"`
//' @aliases Hamming
double dhamming(
    const IntegerMatrix & R1,
    const IntegerMatrix & R2,
    bool normalized = false
  ) {
  
  double ans = 0;
  int n = R1.nrow(), m = R1.ncol();
  for (int i = 0; i<n; ++i) 
    for (int j = 0; j<m; ++j) {
      if (i == j)
        continue;
      
      if (R1(i,j) != R2(i,j))
        ans++;
      
    }
  
  if (normalized) {
    double dn = (double) n;
      ans /= (dn*(dn - 1.0)) ;
  }
    
  return ans;
  
}

//' @name similarity
//' @rdname similarity
//' @section Similarity:
//' - Dennis (44): `"sdennis"` or `"dennis"`
//' @aliases Dennis
double sdennis(
    const IntegerMatrix & M1,
    const IntegerMatrix & M2,
    bool normalized = false
) {
  
  std::vector<double> table = contingency_matrix<double, IntegerMatrix>(M1, M2);
  
  double n = (double) M1.nrow();
  
  return (table[a]*table[d] - table[b]*table[c])/
    sqrt(n*(table[a] + table[b])*(table[a] + table[c]));
  
}

//' @name similarity
//' @rdname similarity
//' @section Similarity:
//' - Yuleq (61): `"syuleq"`
//' @aliases Yuleq
double syuleq(
    const IntegerMatrix & M1,
    const IntegerMatrix & M2,
    bool normalized = false
) {
  
  std::vector<double> table = contingency_matrix<double, IntegerMatrix>(M1, M2);
  
  return (table[a]*table[d] - table[b]*table[c])/(table[a]*table[d] + table[b]*table[c]);
  
}

//' @name similarity
//' @rdname similarity
//' @section Similarity:
//' - Yuleq (63): `"syuleqw"`
//' @aliases Yuleq
double syuleqw(
    const IntegerMatrix & M1,
    const IntegerMatrix & M2,
    bool normalized = false
) {
  
  std::vector<double> table = contingency_matrix<double, IntegerMatrix>(M1, M2);
  
  return (sqrt(table[a]*table[d]) - sqrt(table[b]*table[c]))/
    (sqrt(table[a]*table[d]) + sqrt(table[b]*table[c]));
  
}

//' @name similarity
//' @rdname similarity
//' @section Distance:
//' - Yuleq (62): `"dyuleq"`
//' @aliases Yuleq
double dyuleq(
  const IntegerMatrix & M1,
  const IntegerMatrix & M2,
  bool normalized = false
) {
  
  std::vector<double> table = contingency_matrix<double, IntegerMatrix>(M1, M2);
  
  return 2.0*table[b]*table[c]/(table[a]*table[d] + table[b]*table[c]);
  
}

//' @name similarity
//' @rdname similarity
//' @section Similarity:
//' - Michael (68):  `"smichael"` or `"michael"`
//' @aliases Michael
double smichael(
  const IntegerMatrix & M1,
  const IntegerMatrix & M2,
  bool normalized = false
) {
  
  std::vector<double> table = contingency_matrix<double, IntegerMatrix>(M1, M2);
  
  return 4.0*(table[a]*table[d] - table[b]*table[c])/
    (pow(table[a] + table[d], 2.0) + pow(table[b] + table[c], 2.0));
}

//' @name similarity
//' @rdname similarity
//' @section Similarity:
//' - Peirce (73): `"speirce"` or `"peirce"`
//' @aliases Peirce
double speirce(
  const IntegerMatrix & M1,
  const IntegerMatrix & M2,
  bool normalized = false
) {
  
  std::vector<double> table = contingency_matrix<double, IntegerMatrix>(M1, M2);
  
  return (table[a]*table[b] + table[b]*table[c])/
    (table[a]*table[b] + 2*table[b]*table[c] + table[c]*table[d]);
  
}



// -----------------------------------------------------------------------------

typedef double (*funcPtr)(const IntegerMatrix & M1, const IntegerMatrix & M2, bool normalize);

NumericMatrix allsimilarities(
    const ListOf<IntegerMatrix> & M,
    bool normalized = false,
    funcPtr fun = NULL
) {
  
  int N = M.size();
  int NN = N*(N-1)/2;
  NumericVector ans(NN);
  NumericVector I(NN),J(NN);
  
  int pos = 0;
  for (int i = 0; i < N; ++i)
    for (int j = i; j < N; ++j)
      if (i == j) continue;
      else {
        I[pos] = i + 1;
        J[pos] = j + 1;
        ans[pos++] = fun(M[i], M[j], normalized);
      }
      
      return cbind(I,J,ans);
      
}

void getmetric(std::string s, funcPtr & fun) {
  
  if      (s == "s14" | s == "sph1" | s == "ph1") fun = &sph1;
  else if (s == "hamming" | s == "dhamming")      fun = &dhamming;
  else if (s == "dennis" | s == "sdennis")        fun = &sdennis;
  else if (s == "starwid" | s == "tarwid")        fun = &starwid;
  else if (s == "syuleq")                         fun = &syuleq;
  else if (s == "syuleqw")                        fun = &syuleqw;
  else if (s == "dyuleq")                         fun = &dyuleq;
  else if (s == "smichael" | s == "michael")      fun = &smichael;
  else if (s == "speirce" | s == "peirce")        fun = &speirce;
  else if (s == "sjaccard" | s == "jaccard")      fun = &speirce;
  else Rcpp::stop("The statistic '%s' is not defined.", s);
  
  return ;
}

// [[Rcpp::export(name=".similarity")]]
NumericMatrix similarity(
    const ListOf<IntegerMatrix> & M,
    const std::string & statistic,
    bool normalized=false
  ) {
  
  funcPtr fun;
  getmetric(statistic, fun);
  
  return allsimilarities(M, normalized, fun);
  
}

// No longer needed
#undef a
#undef b
#undef c
#undef d
