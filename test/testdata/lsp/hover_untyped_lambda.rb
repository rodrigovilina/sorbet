# typed: strong

->(arg0) { 1 }
#   ^ hover: T.untyped

->(arg0) do
  arg0.foo
  #    ^^^ error: Call to method `foo` on `T.untyped`
# ^^^^^^^^ error: Value returned from block is `T.untyped`
end
