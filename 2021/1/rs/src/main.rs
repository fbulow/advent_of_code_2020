use std::io;

fn main() {
    let mut value = String::new();
    println!("Enter \"input\"");
    io::stdin().read_line(&mut value).expect("Failed");
    println!("Input: {}", value);
}
