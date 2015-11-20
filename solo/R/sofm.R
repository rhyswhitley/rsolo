# wrapper for loading the SOFM C library
solo <- function(dataset, nodes, iter, width=0.01) {

    # convert to matrix and remove name attribs
    data.in <- unname(as.matrix(dataset))

    # create a list to pass parameters
    settings <- list(nodes = as.integer(nodes),
                     iter = as.integer(iter),
                     width = as.numeric(width)
                     )

    # pass SEXP datatypes as inputs to C++ shared object [sofm] - call function
    sofm.out   <- .Call("solo", data.in, settings, PACKAGE="solo")

    return(sofm.out)
}

