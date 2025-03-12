#include "filetype/filetype.hpp"
#include <gtest/gtest.h>
#include <vector>

class FileTypeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup test data
        png_data = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
        jpeg_data = {0xFF, 0xD8, 0xFF, 0xE0};
        pdf_data = {0x25, 0x50, 0x44, 0x46};
        mp3_data = {0xFF, 0xFB};
        empty_buffer = {};
        invalid_data = {0x00, 0x01, 0x02, 0x03};
    }

    std::vector<uint8_t> png_data;
    std::vector<uint8_t> jpeg_data;
    std::vector<uint8_t> pdf_data;
    std::vector<uint8_t> mp3_data;
    std::vector<uint8_t> empty_buffer;
    std::vector<uint8_t> invalid_data;
};

TEST_F(FileTypeTest, DetectPNG) {
    const filetype::Type* type = filetype::match(png_data);
    ASSERT_NE(type, nullptr);
    EXPECT_EQ(type->mime, "image/png");
    EXPECT_EQ(type->extension, "png");
    EXPECT_TRUE(filetype::is_image(png_data));
}

TEST_F(FileTypeTest, DetectJPEG) {
    const filetype::Type* type = filetype::match(jpeg_data);
    ASSERT_NE(type, nullptr);
    EXPECT_EQ(type->mime, "image/jpeg");
    EXPECT_EQ(type->extension, "jpg");
    EXPECT_TRUE(filetype::is_image(jpeg_data));
}

TEST_F(FileTypeTest, DetectPDF) {
    const filetype::Type* type = filetype::match(pdf_data);
    ASSERT_NE(type, nullptr);
    EXPECT_EQ(type->mime, "application/pdf");
    EXPECT_EQ(type->extension, "pdf");
    EXPECT_TRUE(filetype::is_document(pdf_data));
}

TEST_F(FileTypeTest, DetectMP3) {
    const filetype::Type* type = filetype::match(mp3_data);
    ASSERT_NE(type, nullptr);
    EXPECT_EQ(type->mime, "audio/mpeg");
    EXPECT_EQ(type->extension, "mp3");
    EXPECT_TRUE(filetype::is_audio(mp3_data));
}

TEST_F(FileTypeTest, EmptyBuffer) {
    EXPECT_EQ(filetype::match(empty_buffer), nullptr);
    EXPECT_FALSE(filetype::is_image(empty_buffer));
    EXPECT_FALSE(filetype::is_document(empty_buffer));
    EXPECT_FALSE(filetype::is_archive(empty_buffer));
    EXPECT_FALSE(filetype::is_audio(empty_buffer));
    EXPECT_FALSE(filetype::is_video(empty_buffer));
}

TEST_F(FileTypeTest, InvalidData) {
    EXPECT_EQ(filetype::match(invalid_data), nullptr);
    EXPECT_FALSE(filetype::is_image(invalid_data));
    EXPECT_FALSE(filetype::is_document(invalid_data));
    EXPECT_FALSE(filetype::is_archive(invalid_data));
    EXPECT_FALSE(filetype::is_audio(invalid_data));
    EXPECT_FALSE(filetype::is_video(invalid_data));
}

TEST_F(FileTypeTest, TypeComparison) {
    const filetype::Type* png_type = filetype::match(png_data);
    ASSERT_NE(png_type, nullptr);
    EXPECT_TRUE(filetype::is(png_data, filetype::image::TYPE_PNG));
    EXPECT_FALSE(filetype::is(png_data, filetype::image::TYPE_JPEG));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
