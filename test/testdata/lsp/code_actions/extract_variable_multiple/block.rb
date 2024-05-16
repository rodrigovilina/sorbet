# typed: true
# selective-apply-code-action: refactor.extract
# enable-experimental-lsp-extract-to-variable: true

def block_1(x)
  x + 1
# ^^^^^ apply-code-action: [A] Extract Variable
  1.times do |x|
    x + 1
#   ^^^^^ apply-code-action: [B] Extract Variable
  end
end

def block_2(x)
  x + 1
# ^^^^^ apply-code-action: [C] Extract Variable
# ^^^^^ apply-code-action: [D] Extract Variable (all 2 occurrences)
  1.times do |y|
    x + 1
  end
end

def block_3(x)
  x + 1
  x + 1
# ^^^^^ apply-code-action: [E] Extract Variable
# ^^^^^ apply-code-action: [F] Extract Variable (all 2 occurrences)
  1.times do |x|
    x + 1
#   ^^^^^ apply-code-action: [G] Extract Variable
#   ^^^^^ apply-code-action: [H] Extract Variable (all 2 occurrences)
    x + 1
  end
end
