class UncompressedMap
  attr_accessor :base
  attr_accessor :column_words
  attr_accessor :columns
  attr_accessor :num_blocks
  attr_accessor :blocks
  def initialize
    @base = []
    @column_words = 0
    @columns = []
    @num_blocks = 0
    @blocks = []
  end
end

class Block
  attr_accessor :left, :right, :top, :bottom, :lid
  attr_accessor :arrows
  attr_accessor :slope_type
end

File.open('bil.gmp', 'r') do |f|
  f.seek(398518 - 8)
  header = f.read(8).unpack("a4 I")
  puts "Section: #{header.first}"
  puts "Length:  #{header.last} bytes"
  puts
  map = UncompressedMap.new
  map.base = f.read(256*256*4).unpack("I*")
  raise "after base: #{f.pos}"
  map.column_words = f.read(4).unpack("I").first
  puts "%.2f%%" % ((f.pos - 398418) / header.last.to_f * 100.0)
  map.columns = f.read(map.column_words * 4).unpack("I*")
  puts "%.2f%%" % ((f.pos - 398418) / header.last.to_f * 100.0)
  map.num_blocks = f.read(4).unpack("I").first
  puts "%.2f%%" % ((f.pos - 398418) / header.last.to_f * 100.0)
  0.upto(map.num_blocks - 1) do
    block = Block.new
    block.left, block.right, block.top, block.bottom, block.lid = f.read(2*5).unpack("v*")
    block.arrows = f.read(1).unpack("C")
    block.slope_type = f.read(1).unpack("C")
    map.blocks << block
    puts "%.2f%%" % ((f.pos - 398418) / header.last.to_f * 100.0)
  end
  puts f.pos
  puts f.read(8).unpack("a4 I").inspect

  puts map.base[0..10].inspect
end

