# typed: true
# selective-apply-code-action: refactor.extract

[].each { |x| return x.foo if x.foo}
#                             ^^^^^ apply-code-action: [A] Extract Variable

1.times do |x| 1 + 123 end
#                  ^^^ apply-code-action: [B] Extract Variable

1.times do |x| 1 + 1; 1 + 123 end
#                         ^^^ apply-code-action: [C] Extract Variable

1.times do |x|
  1 + 123
#     ^^^ apply-code-action: [D] Extract Variable
end

1.times do |x|
  1 + 1
  1 + 123
#     ^^^ apply-code-action: [E] Extract Variable
end

1.times do |x|
  1 + 1
  1 + 2; 1 + 123
#            ^^^ apply-code-action: [F] Extract Variable
end
