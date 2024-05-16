# typed: true
# selective-apply-code-action: refactor.extract
# enable-experimental-lsp-extract-to-variable: true

def while_1(x)
  while T.unsafe(nil)
    x + 1
#   ^^^^^ apply-code-action: [A] Extract Variable
#   ^^^^^ apply-code-action: [B] Extract Variable (all 2 occurrences)
    x + 1
  end
end

def while_2(x)
  puts "a dummy line"
  x + 1
  while T.unsafe(nil)
    x + 1
#   ^^^^^ apply-code-action: [C] Extract Variable
#   ^^^^^ apply-code-action: [D] Extract Variable (all 3 occurrences)
    x + 1
  end
end

def while_3(x)
  while x + 1
    x + 1
#   ^^^^^ apply-code-action: [E] Extract Variable
#   ^^^^^ apply-code-action: [F] Extract Variable (all 3 occurrences)
    x + 1
  end
end
