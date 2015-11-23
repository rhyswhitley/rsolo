# wrapper for loading the SOFM C library
solo <- function(dataset, nodes, iter, width=0.01) {

    # convert to matrix and remove name attribs
    data.in <- unname(as.matrix(dataset))

    # create a list to pass parameters
    settings <- list(nodes = as.integer(nodes),
                     iter = as.integer(iter),
                     width = as.numeric(width)
                     )
    # number of covariates
    nvars <- ncol(dataset)

    # pass SEXP datatypes as inputs to C++ shared object [sofm] - call function
    sofm.out   <- .Call("solo", data.in, settings, PACKAGE="solo")
    
    # re-shape the 3D output into a flattened matrix
    flat.mat <- do.call(rbind, do.call(c, sofm.out$weights))
    
    # re-express each covariate's som into a list
    soms <- vector("list", length=nvars)
    for(i in 1:nvars) {
        soms[[i]] <- matrix(flat.mat[,i], nodes, nodes, byrow=TRUE)
    }
    names(soms) <- paste("x", 1:4, sep="")

    return(list("soms"=soms))
}

