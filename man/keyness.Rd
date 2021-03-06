% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/textstat_keyness.R
\name{keyness}
\alias{keyness}
\alias{keyness_chi2_dt}
\alias{keyness_chi2_stats}
\alias{keyness_exact}
\alias{keyness_lr}
\alias{keyness_pmi}
\title{Compute keyness (internal functions)}
\usage{
keyness_chi2_dt(x, correction = c("default", "yates", "williams", "none"))

keyness_chi2_stats(x)

keyness(t, f, sum_t, sum_f)

keyness_exact(x)

keyness_lr(x, correction = c("default", "yates", "williams", "none"))

keyness_pmi(x)
}
\arguments{
\item{x}{a \link{dfm} object}

\item{correction}{implement the Yates correction for 2x2 tables}

\item{t}{(scalar) frequency of target}

\item{f}{(scalar) frequency of reference}

\item{sum_t}{total of all target words}

\item{sum_f}{total of all reference words}
}
\value{
a data.frame of chi2 and p-values with rows named for each feature
}
\description{
Internal function used in textstat_keyness.  Computes \eqn{chi^2} with Yates'
continuity correction for 2x2 tables.
}
\details{
\code{keyness_chi2_dt} uses vectorized computation from data.table
objects.

\code{keyness_chi2_stats} uses element-by-element application of
\link[stats:chisq.test]{chisq.test}.

\code{keyness_exact} computes Fisher's exact using element-by-element
application of \link[stats:fisher.test]{fisher.test}, returning the odds ratio.

\code{keyness_lr} computes the \eqn{G^2} likelihood ratio statistic
using vectorized computation

\code{keyness_pmi} computes the Pointwise Mutual Information stat
using vectorized computation
}
\examples{
dfmat <- dfm(c(d1 = "a a a b b c c c c c c d e f g h h",
               d2 = "a a b c c d d d d e f h"))
quanteda:::keyness_chi2_dt(dfmat)
quanteda:::keyness_chi2_stats(dfmat)
quanteda:::keyness_exact(dfmat)
quanteda:::keyness_lr(dfmat)
quanteda:::keyness_pmi(dfmat)
}
\references{
\url{https://en.wikipedia.org/wiki/Yates's_correction_for_continuity}

\url{http://influentialpoints.com/Training/g-likelihood_ratio_test.htm}
}
\keyword{internal}
\keyword{textstat}
