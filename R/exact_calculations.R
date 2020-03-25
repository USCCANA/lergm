#' Vectorized calculation of ERGM exact log-likelihood
#' 
#' This function can be compared to [ergm::ergm.exact] with the statistics not
#' centered at `x`, the vector of observed statistics.
#' 
#' @param x Matrix. Observed statistics
#' @param params Numeric vector. Parameter values of the model.
#' @template stats
#' @param ... Arguments passed to the default methods.
#' 
#' @section Sufficient statistics:
#' 
#' One of the most important components of `ergmito` is calculating the full
#' support of the model's sufficient statistics. Right now, the package uses
#' the function [ergm::ergm.allstats] which returns a list of two objects:
#'
#' - `weights`: An integer vector of counts.
#' - `statmat`: A numeric matrix with the rows as unique vectors of sufficient
#'   statistics.
#' 
#' Since `ergmito` can vectorize operations, in order to specify weights and
#' statistics matrices for each network in the model, the user needs to pass
#' two lists `stats.weights` and `stats.statmat`. While both lists have to
#' have the same length (since its elements are matched), this needs not to
#' be the case with the networks, as the user can specify a single set of
#' weights and statistics that will be recycled (smartly).
#' 
#' 
#' @examples 
#' data(fivenets)
#' ans <- ergmito(fivenets ~ edges + nodematch("female"))
#' 
#' # This computes the likelihood for all the networks independently
#' with(ans$formulae, {
#'   exact_loglik(
#'     x      = target.stats,
#'     params = coef(ans),
#'     stats.weights = stats.weights,
#'     stats.statmat = stats.statmat
#'   )
#' })
#' 
#' # This should be close to zero
#' with(ans$formulae, {
#'   exact_gradient(
#'     x      = target.stats,
#'     params = coef(ans),
#'     stats.weights = stats.weights,
#'     stats.statmat = stats.statmat
#'   )
#' })
#' 
#' # Finally, the hessian
#' with(ans$formulae, {
#'   exact_hessian(
#'     x      = target.stats,
#'     params = coef(ans),
#'     stats.weights = stats.weights,
#'     stats.statmat = stats.statmat
#'   )
#' })
#' 
#' @export
exact_loglik <- function(x, params, ...) UseMethod("exact_loglik")

#' @export
# @rdname exact_loglik
exact_loglik.ergmito_ptr <- function(x, params, ...) {
  exact_loglik.(x, params = params)
}

#' @export
#' @rdname exact_loglik
exact_loglik.default <- function(
  x,
  params,
  stats.weights,
  stats.statmat,
  ...
) {
  
  # Need to calculate it using chunks of size 200, otherwise it doesn't work(?)
  chunks <- make_chunks(nrow(x), 4e5)
  
  n <- nrow(x)
  
  # Checking the weights and stats mat
  if (n == 1) {
    # If only one observation
    
    if (!is.list(stats.weights))
      stats.weights <- list(stats.weights)
    
    if (!is.list(stats.statmat))
      stats.statmat <- list(stats.statmat)
    
  } else if (n > 1) {
    # If more than 1, then perhaps we need to recycle the values
    
    if (!is.list(stats.weights)) {
      stats.weights <- list(stats.weights)
    } else if (length(stats.weights) != n) {
      stop("length(stats.weights) != nrow(x). When class(stats.weights) == 'list', the number",
           " of elements should match the number of rows in statistics (x).", 
           call. = FALSE)
    }
    
    if (!is.list(stats.statmat)) {
      stats.statmat <- list(stats.statmat)
    } else if (length(stats.statmat) != n) {
      stop("length(stats.statmat) != nrow(x). When class(stats.statmat) == 'list', the number",
           " of elements should match the number of rows in statistics (x).", 
           call. = FALSE)
    }
    
  } else 
    stop("nrow(x) == 0. There are no observed statistics.", call. = FALSE)
  
  # Computing in chunks
  ans <- vector("double", n)
  if (length(stats.weights) > 1L) {
    
    for (s in seq_along(chunks$from)) {
      
      i <- chunks$from[s]
      j <- chunks$to[s]
      
      ergmito_ptr <- new_ergmito_ptr(
        target_stats  = x[i:j, , drop = FALSE],
        stats_weights = stats.weights[i:j],
        stats_statmat = stats.statmat[i:j]
      )
      
      ans[i:j] <- exact_loglik.(ergmito_ptr, params)
      
    }
  } else {
    
    # In this case, this doesn't change
    for (s in seq_along(chunks$from)) {
      
      i <- chunks$from[s]
      j <- chunks$to[s]
      
      # Creating the model pointer
      ergmito_ptr <- new_ergmito_ptr(
        target_stats  = x[i:j, , drop = FALSE],
        stats_weights = stats.weights,
        stats_statmat = stats.statmat
      )
      
      ans[i:j] <- exact_loglik.(ergmito_ptr, params)
      
    }
  }
  
  ans
  
}

# This function uis just used for testing
exact_loglik2 <- function(params, stat0, stats) {
  
  sum(params * stat0) - log(stats$weights %*% exp(stats$statmat %*% params))
  
}

#' @rdname exact_loglik
#' @export
exact_gradient <- function(x, params, ...) UseMethod("exact_gradient")

#' @export
# @rdname exact_loglik
exact_gradient.ergmito_ptr <- function(x, params, ...) {
  exact_gradient.(x, params = params)
}

#' @export
#' @rdname exact_loglik
exact_gradient.default <- function(
  x,
  params,
  stats.weights,
  stats.statmat,
  ...
) {
  
  # Need to calculate it using chunks of size 200, otherwise it doesn't work(?)
  chunks <- make_chunks(nrow(x), 4e5)
  
  n <- nrow(x)
  
  # Checking the weights and stats mat
  if (n == 1) {
    # If only one observation
    
    if (!is.list(stats.weights))
      stats.weights <- list(stats.weights)
    
    if (!is.list(stats.statmat))
      stats.statmat <- list(stats.statmat)
    
  } else if (n > 1) {
    # If more than 1, then perhaps we need to recycle the values
    
    if (!is.list(stats.weights)) {
      stats.weights <- list(stats.weights)
    } else if (length(stats.weights) != n) {
      stop("length(stats.weights) != nrow(x). When class(stats.weights) == 'list', the number",
           " of elements should match the number of rows in statistics (x).", 
           call. = FALSE)
    }
    
    if (!is.list(stats.statmat)) {
      stats.statmat <- list(stats.statmat)
    } else if (length(stats.statmat) != n) {
      stop("length(statmat) != nrow(x). When class(statmat) == 'list', the number",
           " of elements should match the number of rows in statistics (x).", 
           call. = FALSE)
    }
    
  } else 
    stop("nrow(x) == 0. There are no observed statistics.", call. = FALSE)
  
  # Computing in chunks
  ans <- matrix(0, nrow = length(params), ncol=1L)
  for (s in seq_along(chunks$from)) {
    
    i <- chunks$from[s]
    j <- chunks$to[s]
    
    # Creating the model pointer
    ergmito_ptr <- new_ergmito_ptr(
      target_stats  = x[i:j, , drop = FALSE],
      stats_weights = stats.weights[i:j],
      stats_statmat = stats.statmat[i:j]
    )
    
    ans <- ans + exact_gradient.(ergmito_ptr, params)
    
  }
  
  ans
  
}

#' @rdname exact_loglik
#' @export
exact_hessian <- function(
  x,
  params,
  stats.weights,
  stats.statmat
) {
  
  # Need to calculate it using chunks of size 200, otherwise it doesn't work(?)
  chunks <- make_chunks(nrow(x), 4e5)
  
  n <- nrow(x)
  
  # Checking the weights and stats mat
  if (n == 1) {
    # If only one observation
    
    if (!is.list(stats.weights))
      stats.weights <- list(stats.weights)
    
    if (!is.list(stats.statmat))
      stats.statmat <- list(stats.statmat)
    
  } else if (n > 1) {
    # If more than 1, then perhaps we need to recycle the values
    
    if (!is.list(stats.weights)) {
      stats.weights <- list(stats.weights)
    } else if (length(stats.weights) != n) {
      stop("length(stats.weights) != nrow(x). When class(stats.weights) == 'list', the number",
           " of elements should match the number of rows in statistics (x).", 
           call. = FALSE)
    }
    
    if (!is.list(stats.statmat)) {
      stats.statmat <- list(stats.statmat)
    } else if (length(stats.statmat) != n) {
      stop("length(statmat) != nrow(x). When class(statmat) == 'list', the number",
           " of elements should match the number of rows in statistics (x).", 
           call. = FALSE)
    }
    
  } else 
    stop("nrow(x) == 0. There are no observed statistics.", call. = FALSE)
  
  # Computing in chunks
  ans <- matrix(0, nrow = length(params), ncol = length(params))
  for (s in seq_along(chunks$from)) {
    
    i <- chunks$from[s]
    j <- chunks$to[s]
    
    ans <- ans + exact_hessian.(
      x[i:j, ,drop=FALSE],
      params,
      stats_weights = stats.weights[i:j],
      stats_statmat = stats.statmat[i:j]
    )
    
  }
  
  ans
  
}
