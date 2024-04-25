import uuid
import random
import sys

realdatapath = ""

if len(sys.argv) > 2:
    if sys.argv[2] == 'cp':
        realdatapath = "../data/"
    else:     
        realdatapath = ""

# Sample book details
sample_books = [
    {"name": "To Kill a Mockingbird", "author": "Harper Lee", "genre": "Fiction"},
    {"name": "1984", "author": "George Orwell", "genre": "Science Fiction"},
    {"name": "The Great Gatsby", "author": "F. Scott Fitzgerald", "genre": "Classic"},
    {"name": "Pride and Prejudice", "author": "Jane Austen", "genre": "Romance"},
    {"name": "The Catcher in the Rye", "author": "J.D. Salinger", "genre": "Fiction"},
    {"name": "To the Lighthouse", "author": "Virginia Woolf", "genre": "Fiction"},
    {"name": "Moby-Dick", "author": "Herman Melville", "genre": "Adventure"},
    {"name": "Brave New World", "author": "Aldous Huxley", "genre": "Science Fiction"},
    {"name": "The Hobbit", "author": "J.R.R. Tolkien", "genre": "Fantasy"},
    {"name": "The Lord of the Rings", "author": "J.R.R. Tolkien", "genre": "Fantasy"},
    {"name": "Crime and Punishment", "author": "Fyodor Dostoevsky", "genre": "Psychological Fiction"},
    {"name": "One Hundred Years of Solitude", "author": "Gabriel García Márquez", "genre": "Magical Realism"},
    {"name": "The Brothers Karamazov", "author": "Fyodor Dostoevsky", "genre": "Philosophical Fiction"},
    {"name": "Don Quixote", "author": "Miguel de Cervantes", "genre": "Satire"},
    {"name": "War and Peace", "author": "Leo Tolstoy", "genre": "Historical Fiction"},
    {"name": "Anna Karenina", "author": "Leo Tolstoy", "genre": "Realist Novel"},
    {"name": "The Odyssey", "author": "Homer", "genre": "Epic Poetry"},
    {"name": "The Iliad", "author": "Homer", "genre": "Epic Poetry"},
    {"name": "Frankenstein", "author": "Mary Shelley", "genre": "Gothic Fiction"},
    {"name": "The Picture of Dorian Gray", "author": "Oscar Wilde", "genre": "Gothic Fiction"},
    {"name": "Dracula", "author": "Bram Stoker", "genre": "Gothic Horror"},
    {"name": "Jane Eyre", "author": "Charlotte Brontë", "genre": "Gothic Fiction"},
    {"name": "Wuthering Heights", "author": "Emily Brontë", "genre": "Gothic Fiction"},
    {"name": "Alice's Adventures in Wonderland", "author": "Lewis Carroll", "genre": "Fantasy"},
    {"name": "The Adventures of Huckleberry Finn", "author": "Mark Twain", "genre": "Adventure"},
    {"name": "The Adventures of Tom Sawyer", "author": "Mark Twain", "genre": "Adventure"},
    {"name": "The War of the Worlds", "author": "H.G. Wells", "genre": "Science Fiction"},
    {"name": "Around the World in Eighty Days", "author": "Jules Verne", "genre": "Adventure"},
    {"name": "The Time Machine", "author": "H.G. Wells", "genre": "Science Fiction"},
    {"name": "Oliver Twist", "author": "Charles Dickens", "genre": "Novel"},
    {"name": "Great Expectations", "author": "Charles Dickens", "genre": "Novel"},
    {"name": "Little Women", "author": "Louisa May Alcott", "genre": "Novel"},
    {"name": "The Adventures of Sherlock Holmes", "author": "Arthur Conan Doyle", "genre": "Mystery"},
    {"name": "A Tale of Two Cities", "author": "Charles Dickens", "genre": "Novel"},
    {"name": "The Call of the Wild", "author": "Jack London", "genre": "Adventure"},
    {"name": "The Count of Monte Cristo", "author": "Alexandre Dumas", "genre": "Adventure"},
    {"name": "Treasure Island", "author": "Robert Louis Stevenson", "genre": "Adventure"},
    {"name": "Dr. Jekyll and Mr. Hyde", "author": "Robert Louis Stevenson", "genre": "Gothic Fiction"},
    {"name": "A Christmas Carol", "author": "Charles Dickens", "genre": "Novel"},
    {"name": "The Three Musketeers", "author": "Alexandre Dumas", "genre": "Historical Fiction"},
    {"name": "The Secret Garden", "author": "Frances Hodgson Burnett", "genre": "Children's Literature"},
    {"name": "Around the World in Eighty Days", "author": "Jules Verne", "genre": "Adventure"},
    {"name": "The Time Machine", "author": "H.G. Wells", "genre": "Science Fiction"},
    {"name": "Oliver Twist", "author": "Charles Dickens", "genre": "Novel"},
    {"name": "Great Expectations", "author": "Charles Dickens", "genre": "Novel"},
    {"name": "Little Women", "author": "Louisa May Alcott", "genre": "Novel"},
    {"name": "The Adventures of Sherlock Holmes", "author": "Arthur Conan Doyle", "genre": "Mystery"},
    {"name": "A Tale of Two Cities", "author": "Charles Dickens", "genre": "Novel"},
    {"name": "The Call of the Wild", "author": "Jack London", "genre": "Adventure"},
    {"name": "The Count of Monte Cristo", "author": "Alexandre Dumas", "genre": "Adventure"},
    {"name": "Treasure Island", "author": "Robert Louis Stevenson", "genre": "Adventure"},
    {"name": "Dr. Jekyll and Mr. Hyde", "author": "Robert Louis Stevenson", "genre": "Gothic Fiction"},
    {"name": "A Christmas Carol", "author": "Charles Dickens", "genre": "Novel"},
    {"name": "The Three Musketeers", "author": "Alexandre Dumas", "genre": "Historical Fiction"},
    {"name": "The Secret Garden", "author": "Frances Hodgson Burnett", "genre": "Children's Literature"},
    {"name": "Alice's Adventures in Wonderland", "author": "Lewis Carroll", "genre": "Fantasy"},
    {"name": "Gulliver's Travels", "author": "Jonathan Swift", "genre": "Satire"}
]

#

# Sample user details
sample_users = [
    {"name": "Alice", "access_level": "admin"},
    {"name": "Bob", "access_level": "student"},
    {"name": "Charlie", "access_level": "student"},
    {"name": "David", "access_level": "student"},
    {"name": "Eve", "access_level": "admin"}
]

# Function to generate a random UUID
def generate_uuid():
    return str(uuid.uuid4())

# Function to generate book details
def generate_book():
    book_details = random.choice(sample_books)
    book_uuid = generate_uuid()
    book_name = book_details["name"]
    book_author = book_details["author"]
    book_genre = book_details["genre"]
    book_price = round(random.uniform(5.0, 50.0), 2)
    published_year = random.randint(1900, 2022)
    num_copies = random.randint(1, 10)
    #num_borrowed = random.randint(0, num_copies)
    num_borrowed = 0

    borrowed_people = random.sample([generate_uuid() for _ in range(len(sample_users))], num_borrowed)

    return (book_uuid, book_name, book_author, book_genre, book_price, published_year, num_copies, num_borrowed, borrowed_people)

# Function to generate user details
def generate_user():
    user_details = random.choice(sample_users)
    user_uuid = generate_uuid()
    user_name = user_details["name"]
    user_access_level = user_details["access_level"]
    return (user_uuid, user_name, user_access_level)

# Function to write book details to file
def write_books_to_file(num_books, num_users):
    bindex_file = open(realdatapath + "BIndex.txt", "w")
    for _ in range(num_books):
        book_details = generate_book()
        book_uuid = book_details[0]
        bindex_file.write(book_uuid + "\n")

        book_file = open(realdatapath + "B-" + book_uuid + ".txt", "w")
        book_file.write(book_uuid + "\n")
        book_file.write(book_details[1] + "\n")
        book_file.write(book_details[2] + "\n")
        book_file.write(book_details[3] + "\n")
        book_file.write(str(book_details[4]) + "\n")
        book_file.write(str(book_details[5]) + "\n")
        book_file.write(str(book_details[6]) + "\n")
        book_file.write(str(book_details[7]) + "\n")
        for person_uuid in book_details[8]:
            book_file.write(person_uuid + "\n")
        book_file.close()

    bindex_file.close()

# Function to write user details to file
def write_users_to_file(num_users):
    uindex_file = open(realdatapath + "UIndex.txt", "w")
    for _ in range(num_users):
        user_details = generate_user()
        uindex_file.write(user_details[0] + "\n")

        user_file = open(realdatapath + "U-" + user_details[0] + ".txt", "w")
        user_file.write(user_details[0] + "\n")
        user_file.write(user_details[1] + "\n")
        user_file.write(user_details[2] + "\n")
        user_file.close()

    uindex_file.close()

# Number of books and users to generate
num_books_to_generate = int(sys.argv[1])
num_users_to_generate = 5

# Generate and write book details to file
write_books_to_file(num_books_to_generate, num_users_to_generate)

# Generate and write user details to file
write_users_to_file(num_users_to_generate)
