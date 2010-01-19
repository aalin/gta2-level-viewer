require 'GD'
pages = []

File.open('ste.sty', 'r') do |f|
  f.seek(4063254 - 8)
  header = f.read(8).unpack("a4 I")
  puts "Section: #{header.first}"
  puts "Length:  #{header.last} bytes"
  puts

  page = f.read(64*256*4).unpack("I*")
  puts "page size: #{page.size}" 

  puts "num pages: #{header.last / 4 / page.size}"

  img = GD::Image.newTrueColor(64, 256)
  page.each_with_index do |value, i|
    color = img.colorAllocate((value >> 16) & 0xff, (value >> 8) & 0xff, value & 0xff)
    img.setPixel(i % 64, i / 64, color)
    puts "#{i%64}x#{i/64}: %s" % value.to_s(16)
  end
  File.open('test.png', 'w') {|f| img.png(f) }
end

