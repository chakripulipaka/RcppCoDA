x <- matrix(runif(300), 100, 3)
x <- clo(x)

test_that("clo sums to 1", {
  expect_equal(colSums(x), rep(1, ncol(x)))
})


test_that("clo correct on vectors", {
  x1 <- x[,1,drop=T]
  y <- clo(x1)
  expect_equal(matrix(x1/sum(x1)), y)
  expect_equal(sum(y), 1)
})


test_that("clo correct on matricies", {
  y <- clo(x)
  y.true <- sweep(x, 2, colSums(x), FUN=`/`)
  expect_equal(y.true, y)
  expect_equal(colSums(y), rep(1, 3))
})


test_that("center correct on vectors", {
  x <- runif(100)
  expect_equal(matrix(x-mean(x)), center(x))
  expect_equal(sum(center(x)), 0)
})


test_that("center correct on matricies", {
  x <- matrix(runif(300), 100, 3)
  y <- center(x)
  y.true <- sweep(x, 2, mean(x), FUN=`-`)
  expect_equal(center(x), y.true)
  expect_equal(colSums(y), rep(0, 3))
})

test_that("linForm Correct", {
  X <- matrix(runif(300), 100, 3)
  X <- array(x, dim=c(2,4,3))
  
  # Test Simple case
  V <- matrix(rnorm(4*5), 5,4)
  Y = array(0, dim=c(c(2,5,3)))
  for (i in 1:2){
    Y[i,,] <- V%*%X[i,,]
  }
  expect_error(linForm(X, V))
  expect_equal(Y, linForm(X, V,b=2))
  
  # Test case where V2=I
  V <- matrix(rnorm(5*3), 5,3)
  Y <- array(0, dim=c(2, 6, 3))
  for (i in 1:2){
    Y[i,1:5,] <- V%*%X[i,1:3,]
    Y[i,6,] <- X[i,4,]
  }
  expect_equal(Y, linForm(X, V, b=2))
  
  # test simple case where V1 and V2 are given
  V1 <- matrix(rnorm(5*3), 5,3)
  V2 <- matrix(rnorm(1))
  X <- matrix(rnorm(4*2), 4, 2)
  Y <- matrix(0, 6, 2)
  Y[1:5,] <- V1 %*% X[1:3,]
  Y[6,] <- V2 %*% X[4,]
  expect_equal(Y, linForm(X, V1, V2))
  
  # Test case where V2 is given
  X <- matrix(runif(300), 100, 3)
  X <- array(x, dim=c(2,4,3))
  V1 <- matrix(rnorm(5*3), 5,3)
  V2 <- matrix(rnorm(1))
  Y <- array(0, dim=c(2, 6, 3))
  for (i in 1:2){
    Y[i,1:5,] <- V1%*%X[i,1:3,]
    Y[i,6,] <- V2%*%X[i,4,]
  }
  expect_equal(Y, linForm(X, V1,V2, b=2))
})
