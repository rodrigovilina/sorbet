# typed: true
# selective-apply-code-action: refactor.extract
# enable-experimental-lsp-extract-to-variable: true

def foo(x)
end

a = T.unsafe(1)
a_ = a&.to_s
#    ^ apply-code-action: [A] Extract Variable (this occurrence only)

b = T.unsafe(1)
foo(b&.foo) do
#   ^ apply-code-action: [B] Extract Variable (this occurrence only)
  c = T.unsafe(1)
  c&.foo
# ^ apply-code-action: [C] Extract Variable (this occurrence only)
  d = T.unsafe(1)
  puts(d&.foo)
#      ^ apply-code-action: [D] Extract Variable (this occurrence only)
end

