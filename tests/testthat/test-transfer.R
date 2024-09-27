test_that("transfers of data correct", {
  X <- matrix(abs(rnorm(10)), 5, 2)
  X <- clo(X)
  X.ilr <- ilr(X)
  X.clr <- clr(X)
  X.alr <- alr(X)
  V <- ilrContrast(5)
  expect_equal(X.clr, icTransfer(V)%*%X.ilr)
  expect_equal(X.ilr, ciTransfer(V)%*%X.clr)
  
  
  expect_equal(X.clr, ilr2clr(X.ilr, V))
  expect_equal(X.ilr, clr2ilr(X.clr, V))
  expect_equal(X.ilr, ilr2ilr(X.ilr, V, V))
  expect_equal(X.ilr, alr2ilr(X.alr, 5, V))
  expect_equal(X.alr, ilr2alr(X.ilr, V, 5))
  expect_equal(X.clr, alr2clr(X.alr, 5))
  expect_equal(X.alr, clr2alr(X.clr, 5))
  expect_equal(alr2alr(X.alr, 5, 3), ilr2alr(X.ilr, V, 3))

})